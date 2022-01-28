#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

using namespace std;

#define MESSAGE_LENGTH 2048 // Максимальный размер буфера для данных
#define PORT 7777 // Будем использовать этот номер порта

struct sockaddr_in serveraddress, client;
socklen_t length;
int sockert_file_descriptor, connection, bind_status, connection_status;
char message[MESSAGE_LENGTH];

int main()
{
    // Создадим сокет
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockert_file_descriptor == -1) {
        cout << "Не удалось создать сокет.!" << endl;
        exit(1);
    }
    // 
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим номер порта для связи
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress,
        sizeof(serveraddress));
    if (bind_status == -1) {
        cout << "Не удалось выполнить привязку сокета.!" << endl;
        exit(1);
    }
    // Поставим сервер на прием данных 
    connection_status = listen(sockert_file_descriptor, 5);
    if (connection_status == -1) {
        cout << "Сокет не может прослушивать новые подключения.!" << endl;
        exit(1);
    }
    else
    {
        cout << "Сервер прослушивает новое соединение:" << endl;
// начало действия программы:

    }
    length = sizeof(client);
    connection = accept(sockert_file_descriptor, (struct sockaddr*)&client, &length);
    if (connection == -1) {
        cout << "Сервер не может принять данные от клиента.!" << endl;
        exit(1);
    }
    // Communication Establishment
    while (1)
    {

        bzero(message, MESSAGE_LENGTH);
        cout << "read 1" << endl;
        read(connection, message, sizeof(message));
        cout << "read 1" << endl;
                   
       bzero(message, MESSAGE_LENGTH);
       strcpy(message, "меню: 1. Регистрация. 2. Авторизация и работа в чате");
       cout << "write 1" << endl;
       ssize_t bytes = write(connection, message, sizeof(message));
       if (bytes >= 0)
       {
           cout << "Данные отправлены клиенту" << endl;
       }


       cout << "write 2" << endl;


       bzero(message, MESSAGE_LENGTH);
       cout << "read 3" << endl;
       read(connection, message, sizeof(message));
       cout << "read 4" << endl;
       if (strncmp("1", message, 1) == 0)
       {
          bzero(message, MESSAGE_LENGTH);
          strcpy(message, "Введите ваш логин");
          cout << "write 3" << endl;
          ssize_t bytes1 = write(connection, message, sizeof(message));
          if (bytes >= 0) {
              cout << "Данные отправлены клиенту 2" << endl;
          }

          cout << "write 4" << endl;

          bzero(message, MESSAGE_LENGTH);
          cout << "read 5" << endl;
          read(connection, message, sizeof(message));
          cout << "read 6" << endl;

          string user_login(message);
   
          bzero(message, MESSAGE_LENGTH);
          strcpy(message, "Введите ваше имя");
          cout << "write 5" << endl;
          ssize_t bytes2 = write(connection, message, sizeof(message));
          if (bytes >= 0) {
              cout << "Данные отправлены клиенту 3" << endl;
          }
          cout << "write 6" << endl;

          bzero(message, MESSAGE_LENGTH);
          read(connection, message, sizeof(message));

          string user_name(message);

          bzero(message, MESSAGE_LENGTH);
          strcpy(message, "Введите ваш пароль");
          cout << "write 7" << endl;
          ssize_t bytes3 = write(connection, message, sizeof(message));
          cout << "write 8" << endl;
          if (bytes >= 0)
          {
              cout << "Данные отправлены клиенту 4" << endl;
          }

          bzero(message, MESSAGE_LENGTH);
          read(connection, message, sizeof(message));

          string user_password(message);
                 
          bzero(message, MESSAGE_LENGTH);
          strcpy(message, "Пользователь зарегистрирован");
          cout << "write 9" << endl;
          ssize_t bytes4 = write(connection, message, sizeof(message));
          cout << "write 10" << endl;


          cout << "пользователь добавлен в вектор" << endl;
       }


    }
    // закрываем сокет, завершаем соединение
    close(sockert_file_descriptor);
    return 0;
}