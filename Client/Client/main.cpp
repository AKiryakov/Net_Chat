#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777 // Будем использовать этот номер порта

int socket_file_descriptor, connection;
struct sockaddr_in serveraddress, client;
char message[MESSAGE_LENGTH];
int main() {
    // Создадим сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        cout << "Не удалось создать сокет!" << endl;
        exit(1);
    }

    // Установим адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Зададим номер порта
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Установим соединение с сервером
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (connection == -1) {
        cout << "Не удалось установить соединение с сервером.!" << endl;
        exit(1);
    }
    // Взаимодействие с сервером
    cout << "Для начала работы программы отправьте любое сообщение на сервер" << endl;
    while (1)
    {
  
        bzero(message, sizeof(message));
        cin >> message;
        cout << "write 1" << endl;
        ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
        if (bytes >= 0) {
            cout << "Данные отправлены на сервер" << endl;
        }
        cout << "write 2" << endl;

       bzero(message, sizeof(message));
       cout << "read 1" << endl;
       read(socket_file_descriptor, message, sizeof(message));
       cout << "read 2" << endl;
       cout << message << endl;
    }
    // закрываем сокет, завершаем соединение
    close(socket_file_descriptor);
    return 0;
}