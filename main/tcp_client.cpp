#include "tcp_client.h"

// WiFiClient 连接
// 发送 GET 请求
ResponseData sendGetRequest(const String &endpoint)
{
    // 打印调试信息
    Serial.print("Connecting to ");
    Serial.println(SERVER_ADDRESS);

    if (!client.connect(SERVER_ADDRESS, SERVER_PORT))
    {
        Serial.println("Connection failed");
        return ResponseData{-1, "Connection failed"};
    }

    // 构建 HTTP GET 请求
    String request = "GET " + endpoint + " HTTP/1.1\r\n" +
                     "Host: " + String(SERVER_ADDRESS) + "\r\n" +
                     "Connection: close\r\n\r\n";

    // 发送请求
    client.print(request);
    Serial.println("GET request sent");

    // 等待服务器响应
    while (client.connected() && !client.available())
    {
        delay(10); // 等待数据
    }

    // 读取响应
    ResponseData response;
    response.statusCode = -1;
    response.body = "";

    while (client.available())
    {
        response.body += client.readStringUntil('\r');
    }

    response.statusCode = 200; // 假设成功的状态码
    Serial.println("Response:");
    Serial.println(response.body);

    // 断开连接
    client.stop();
    Serial.println("Disconnected");

    return response;
}

// 发送 POST 请求
ResponseData sendPostRequest(const String &endpoint, const String &body)
{
    // 打印调试信息
    Serial.print("Connecting to ");
    Serial.println(SERVER_ADDRESS);

    if (!client.connect(SERVER_ADDRESS, SERVER_PORT))
    {
        Serial.println("Connection failed");
        return ResponseData{-1, "Connection failed"};
    }

    // 构建 HTTP POST 请求
    String request = "POST " + endpoint + " HTTP/1.1\r\n" +
                     "Host: " + String(SERVER_ADDRESS) + "\r\n" +
                     "Connection: close\r\n" +
                     "Content-Type: application/json\r\n" +
                     "Content-Length: " + String(body.length()) + "\r\n" +
                     "\r\n" +
                     body + "\r\n";

    // 发送请求
    client.print(request);
    Serial.println("POST request sent");

    // 等待服务器响应
    while (client.connected() && !client.available())
    {
        delay(10); // 等待数据
    }

    // 读取响应
    ResponseData response;
    response.statusCode = -1;
    response.body = "";

    while (client.available())
    {
        response.body += client.readStringUntil('\r');
    }

    response.statusCode = 200; // 假设成功的状态码
    Serial.println("Response:");
    Serial.println(response.body);

    // 断开连接
    client.stop();
    Serial.println("Disconnected");

    return response;
}
