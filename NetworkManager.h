#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>
#include <functional>
#include <windows.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

// Maximum size of a UDP packet
#define MAX_PACKET_SIZE 1024

// Default port for the game
#define DEFAULT_PORT "27015"

// Network message types
enum class MessageType : uint8_t
{
    CONNECT_REQUEST = 1,
    CONNECT_ACCEPT = 2,
    DISCONNECT = 3,
    TANK_UPDATE = 4,
    BULLET_FIRED = 5,
    GAME_STATE = 6,
    CHAT_MESSAGE = 7,
    BULLET_HIT = 8,
    GAME_OVER = 9,
    GAME_RESET = 10
};

// Network message header
struct MessageHeader
{
    MessageType type;
    uint32_t size;
};

// Tank state for network transmission
struct NetworkTankState
{
    float x;
    float y;
    float z;
    float bodyRotation;
    float turretRotation;
    int health;
};

// Bullet state for network transmission
struct NetworkBulletState
{
    float x;
    float y;
    float z;
    float dirX;
    float dirY;
    float dirZ;
    int damage;
};

// Bullet hit notification for network transmission
struct NetworkBulletHit
{
    int damage;
    bool isPlayerHit; // true if the local player was hit, false if remote player was hit
};

// Game state for network transmission
struct NetworkGameState
{
    bool gameOver;
    bool playerWon; // true if local player won, false if remote player won
};

// Network manager class for handling UDP communication
class NetworkManager
{
public:
    // Initialize Winsock
    static bool Initialize();

    // Clean up Winsock
    static void Cleanup();

    NetworkManager();
    ~NetworkManager();

    // Start as server
    bool StartServer();

    // Start as client and connect to server
    bool ConnectToServer(const std::string &serverIP);

    // Send data to connected peer
    bool SendData(const void *data, int size);

    // Send a message with a specific type
    bool SendMessage(MessageType type, const void *data, int size);

    // Send a text message
    bool SendTextMessage(const std::string &message);

    // Send tank state
    bool SendTankState(const NetworkTankState &state);

    // Send bullet fired
    bool SendBulletFired(const NetworkBulletState &state);

    // Send bullet hit notification
    bool SendBulletHit(const NetworkBulletHit &hit);

    // Send game state update
    bool SendGameState(const NetworkGameState &state);

    // Send game reset request
    bool SendGameReset();

    // Process received data
    void ProcessReceivedData();

    // Check if connected
    bool IsConnected() const { return m_connected; }

    // Check if server
    bool IsServer() const { return m_isServer; }

    // Set callback for when a message is received
    void SetMessageCallback(std::function<void(MessageType, const void *, int)> callback)
    {
        m_messageCallback = callback;
    }

    // Set callback for when a connection is established
    void SetConnectCallback(std::function<void(bool)> callback)
    {
        m_connectCallback = callback;
    }

    // Set callback for when a connection is lost
    void SetDisconnectCallback(std::function<void()> callback)
    {
        m_disconnectCallback = callback;
    }

    // Get the IP address of the connected peer
    std::string GetPeerAddress() const { return m_peerAddress; }

private:
    // Socket for communication
    SOCKET m_socket;

    // Address of the peer
    sockaddr_in m_peerAddr;
    std::string m_peerAddress;

    // Thread for receiving data
    HANDLE m_receiveThread;
    bool m_running;

    // Connection state
    bool m_connected;
    bool m_isServer;

    // Buffer for receiving data
    char m_receiveBuffer[MAX_PACKET_SIZE];

    // Callbacks
    std::function<void(MessageType, const void *, int)> m_messageCallback;
    std::function<void(bool)> m_connectCallback;
    std::function<void()> m_disconnectCallback;

    // Receive data from socket
    void ReceiveThread();

    // Static thread function for _beginthreadex
    static unsigned int __stdcall ThreadProc(void *param);
};
