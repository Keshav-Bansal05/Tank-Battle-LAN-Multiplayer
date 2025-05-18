#include "NetworkManager.h"
#include <iostream>

// Initialize Winsock
bool NetworkManager::Initialize()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return false;
    }
    return true;
}

// Clean up Winsock
void NetworkManager::Cleanup()
{
    WSACleanup();
}

NetworkManager::NetworkManager()
    : m_socket(INVALID_SOCKET),
      m_receiveThread(NULL),
      m_running(false),
      m_connected(false),
      m_isServer(false)
{
    memset(&m_peerAddr, 0, sizeof(m_peerAddr));
    memset(m_receiveBuffer, 0, MAX_PACKET_SIZE);
}

NetworkManager::~NetworkManager()
{
    // Stop the receive thread
    m_running = false;
    if (m_receiveThread != NULL)
    {
        WaitForSingleObject(m_receiveThread, 1000);
        CloseHandle(m_receiveThread);
        m_receiveThread = NULL;
    }

    // Close the socket
    if (m_socket != INVALID_SOCKET)
    {
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }
}

bool NetworkManager::StartServer()
{
    // Create a UDP socket
    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_socket == INVALID_SOCKET)
    {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        return false;
    }

    // Set up the server address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(DEFAULT_PORT));
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(m_socket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
        return false;
    }

    // Set non-blocking mode
    u_long mode = 1;
    if (ioctlsocket(m_socket, FIONBIO, &mode) == SOCKET_ERROR)
    {
        std::cerr << "Failed to set non-blocking mode: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
        return false;
    }

    // Start the receive thread
    m_running = true;
    m_isServer = true;
    m_receiveThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, this, 0, NULL);

    std::cout << "Server started on port " << DEFAULT_PORT << std::endl;
    return true;
}

bool NetworkManager::ConnectToServer(const std::string &serverIP)
{
    // Log connection attempt
    std::cout << "Network Manager: Connecting to server at " << serverIP << std::endl;

    // Create a UDP socket
    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_socket == INVALID_SOCKET)
    {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        return false;
    }

    // Set up the server address
    m_peerAddr.sin_family = AF_INET;
    m_peerAddr.sin_port = htons(atoi(DEFAULT_PORT));

    // Clean the IP address string to ensure it's valid
    std::string cleanedIP;

    // First, check if the IP is already valid
    bool isValid = true;
    for (char c : serverIP)
    {
        if (!((c >= '0' && c <= '9') || c == '.'))
        {
            isValid = false;
            break;
        }
    }

    if (isValid)
    {
        // IP is already valid, use as is
        cleanedIP = serverIP;
    }
    else
    {
        // IP needs cleaning, extract only digits and dots
        for (char c : serverIP)
        {
            // Only keep digits and dots for IP address
            if ((c >= '0' && c <= '9') || c == '.')
            {
                cleanedIP += c;
            }
            else if (c == ',')
            {
                // Replace commas with dots (common typo)
                cleanedIP += '.';
            }
        }
    }

    // Special case for localhost
    if (serverIP == "localhost" || serverIP == "LOCALHOST")
    {
        cleanedIP = "127.0.0.1";
    }

    // Convert IP address string to network address
    unsigned long addr = inet_addr(cleanedIP.c_str());
    if (addr == INADDR_NONE)
    {
        std::cerr << "Invalid IP address format: " << cleanedIP << std::endl;
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
        return false;
    }

    m_peerAddr.sin_addr.s_addr = addr;
    m_peerAddress = cleanedIP; // Store the cleaned IP

    // Set non-blocking mode
    u_long mode = 1;
    if (ioctlsocket(m_socket, FIONBIO, &mode) == SOCKET_ERROR)
    {
        std::cerr << "Failed to set non-blocking mode: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
        return false;
    }

    // Send a connection request
    MessageHeader header;
    header.type = MessageType::CONNECT_REQUEST;
    header.size = sizeof(MessageHeader);

    if (sendto(m_socket, (const char *)&header, sizeof(header), 0,
               (sockaddr *)&m_peerAddr, sizeof(m_peerAddr)) == SOCKET_ERROR)
    {
        std::cerr << "Failed to send connection request: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
        return false;
    }

    // Start the receive thread
    m_running = true;
    m_isServer = false;
    m_receiveThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, this, 0, NULL);

    std::cout << "Connecting to server at " << serverIP << ":" << DEFAULT_PORT << std::endl;
    return true;
}

bool NetworkManager::SendData(const void *data, int size)
{
    if (!m_connected)
    {
        std::cerr << "Not connected to a peer" << std::endl;
        return false;
    }

    if (sendto(m_socket, (const char *)data, size, 0,
               (sockaddr *)&m_peerAddr, sizeof(m_peerAddr)) == SOCKET_ERROR)
    {
        std::cerr << "Failed to send data: " << WSAGetLastError() << std::endl;
        return false;
    }

    return true;
}

bool NetworkManager::SendMessage(MessageType type, const void *data, int size)
{
    // Create a buffer for the message
    std::vector<char> buffer(sizeof(MessageHeader) + size);
    MessageHeader *header = (MessageHeader *)buffer.data();
    header->type = type;
    header->size = sizeof(MessageHeader) + size;

    // Copy the data after the header
    if (size > 0 && data != nullptr)
    {
        memcpy(buffer.data() + sizeof(MessageHeader), data, size);
    }

    // Send the message
    return SendData(buffer.data(), buffer.size());
}

bool NetworkManager::SendTextMessage(const std::string &message)
{
    return SendMessage(MessageType::CHAT_MESSAGE, message.c_str(), message.length() + 1);
}

bool NetworkManager::SendTankState(const NetworkTankState &state)
{
    return SendMessage(MessageType::TANK_UPDATE, &state, sizeof(state));
}

bool NetworkManager::SendBulletFired(const NetworkBulletState &state)
{
    return SendMessage(MessageType::BULLET_FIRED, &state, sizeof(state));
}

bool NetworkManager::SendBulletHit(const NetworkBulletHit &hit)
{
    return SendMessage(MessageType::BULLET_HIT, &hit, sizeof(hit));
}

bool NetworkManager::SendGameState(const NetworkGameState &state)
{
    return SendMessage(MessageType::GAME_STATE, &state, sizeof(state));
}

bool NetworkManager::SendGameReset()
{
    return SendMessage(MessageType::GAME_RESET, nullptr, 0);
}

// ProcessReceivedData is handled in the receive thread

// Static thread function
unsigned int __stdcall NetworkManager::ThreadProc(void *param)
{
    NetworkManager *self = static_cast<NetworkManager *>(param);
    self->ReceiveThread();
    return 0;
}

void NetworkManager::ReceiveThread()
{
    while (m_running)
    {
        // Receive data
        sockaddr_in senderAddr;
        int senderAddrSize = sizeof(senderAddr);
        int bytesReceived = recvfrom(m_socket, m_receiveBuffer, MAX_PACKET_SIZE, 0,
                                     (sockaddr *)&senderAddr, &senderAddrSize);

        if (bytesReceived > 0)
        {
            // Process the received data
            MessageHeader *header = (MessageHeader *)m_receiveBuffer;

            // Handle connection messages
            if (header->type == MessageType::CONNECT_REQUEST)
            {
                if (m_isServer && !m_connected)
                {
                    // Store the client's address
                    memcpy(&m_peerAddr, &senderAddr, sizeof(senderAddr));

                    // Get the client's IP address as a string
                    char *ipStr = inet_ntoa(senderAddr.sin_addr);
                    m_peerAddress = ipStr;

                    // Send connection accept
                    MessageHeader response;
                    response.type = MessageType::CONNECT_ACCEPT;
                    response.size = sizeof(MessageHeader);

                    sendto(m_socket, (const char *)&response, sizeof(response), 0,
                           (sockaddr *)&m_peerAddr, sizeof(m_peerAddr));

                    // Set connected state
                    m_connected = true;

                    // Call the connect callback
                    if (m_connectCallback)
                    {
                        m_connectCallback(true);
                    }

                    std::cout << "Client connected from " << m_peerAddress << std::endl;
                }
            }
            else if (header->type == MessageType::CONNECT_ACCEPT)
            {
                if (!m_isServer && !m_connected)
                {
                    // Set connected state
                    m_connected = true;

                    // Call the connect callback
                    if (m_connectCallback)
                    {
                        m_connectCallback(true);
                    }

                    std::cout << "Connected to server" << std::endl;
                }
            }
            else if (header->type == MessageType::DISCONNECT)
            {
                // Handle disconnect
                m_connected = false;

                // Call the disconnect callback
                if (m_disconnectCallback)
                {
                    m_disconnectCallback();
                }

                std::cout << "Disconnected from peer" << std::endl;
            }
            else if (m_connected)
            {
                // Call the message callback for other message types
                if (m_messageCallback)
                {
                    m_messageCallback(header->type,
                                      m_receiveBuffer + sizeof(MessageHeader),
                                      bytesReceived - sizeof(MessageHeader));
                }
            }
        }
        else if (bytesReceived == SOCKET_ERROR)
        {
            int error = WSAGetLastError();
            if (error != WSAEWOULDBLOCK)
            {
                std::cerr << "Error receiving data: " << error << std::endl;

                // Handle disconnection
                if (m_connected)
                {
                    m_connected = false;

                    // Call the disconnect callback
                    if (m_disconnectCallback)
                    {
                        m_disconnectCallback();
                    }

                    std::cout << "Connection lost" << std::endl;
                }
            }
        }

        // Sleep to avoid high CPU usage
        Sleep(10);
    }
}
