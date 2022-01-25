#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

using namespace std;

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777 // Будем использовать этот номер порта

struct sockaddr_in serveraddress, client;
socklen_t length;
int sockert_file_descriptor, connection, bind_status, connection_status;
char message[MESSAGE_LENGTH];

int main() {
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
        read(connection, message, sizeof(message));
        if (strncmp("end", message, 3) == 0) {
            cout << "Клиент завершает работу." << endl;
            cout << "Сервер завершает работу." << endl;
            break;
        }
//cout << "Данные, полученные от клиента: " << message << endl;
// после получения от клиента
        bzero(message, MESSAGE_LENGTH);
//        cout << "Введите сообщение, которое вы хотите отправить клиенту: " << endl;
//        cin >> message;





// ВОПРОС ТУТ:
// 
// я хочу, чтобы серевер не предлагал ввести с экрна текст сообщения для отправки клиенту,
// а после получения любого сообщения от клиеннта передал по сети меню чата "меню: 1. Авторизация. 2. Регистрация. 3. Работа в чате"
// однако так это сделать не получается:
// ЧТО Я ДЕЛАЮ НЕПРАВИЛЬНО И КАК ПЕРЕДАТЬ КЛИЕНТУ ЗАГОТОВЛЕННЫЙ ТЕКСТ?
  
//   если message попытаться присвоить какое-либо значение, программа не компилируется:
        message = 'меню: 1. Авторизация. 2. Регистрация. 3. Работа в чате';

        ssize_t bytes = write(connection, message, sizeof(message));
        // Если передали >= 0  байт, значит пересылка прошла успешно
        if (bytes >= 0) {
            cout << "Данные успешно отправлены клиенту.!" << endl;
        }
    }
    // закрываем сокет, завершаем соединение
    close(sockert_file_descriptor);
    return 0;
}