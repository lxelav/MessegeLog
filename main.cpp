#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <windows.h>
#include <sstream>

using namespace std;

//Класс, который представляет сообщение пользователя. в нем определены поля userName, time, message.
class Message
{
    string userName;
    string time;
    string message;

public:
    //Контсруктор класса Message, который присваивает переменным userName, time, message значения.
    Message(const string& userName, const string& time, const string& message)
    {
        this->userName = userName;
        this->time = time;
        this->message = message;
    }

    //Перегрузка оператора сравнения <. Сначала сравнивает по имени, а если имя одинаковые, то по времени.
    //Перегружаем этот оператор для корректной работы контейнера set.
    bool operator<(const Message& obj) const
    {
        if (this->userName != obj.userName)
            return this->userName < obj.userName;
        return this->time < obj.time;
    }

    //Геттеры и сеттеры для работы с закрытыми членами класса.
    string getUserName() const
    {
        return userName;
    }

    void setUserName(const string& name)
    {
        userName = name;
    }

    string getTime() const
    {
        return time;
    }

    void setTime(const string& time)
    {
        this->time = time;
    }

    string getMessage() const
    {
        return message;
    }

    void setMessage(const string& m)
    {
        message = m;
    }
};

int main()
{
    //Функции из заголовочного файла windows.h для корректного ввода/вывода кириллицы.
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    set<Message> messages;

    ifstream file;
    file.open("input_file.txt");

    //Обработка входного файла
    string line;
    while (getline(file, line))
    {
        /*Создается объект stringstream с именем ss 
        и инициализируется считанной строкой line. stringstream позволяет работать со 
        строками как с потоками данных, что облегчает разбор отдельных элементов.*/
        stringstream ss(line);

        string user_name, time, message;
        ss >> user_name >> time;
        getline(ss, message);

        //Создается объект Message и добавляется в контейнер set
        Message user_message(user_name, time, message);
        messages.insert(user_message);
    }

    bool flag = true;
    while (flag)
    {
        int choice;
        cout << "Введите номер опции, которую хотите выполнить:\n"
            << "1. Вывод всех сообщений заданного пользователя\n"
            << "2. Вывод сообщений пользователя для заданного временного интервала\n"
            << "3. Вывод всех сообщений из заданного временного интервала\n"
            << "4. Удаление заданного сообщения\n"
            << "5. Удаление сообщений заданного пользователя\n";
        cout << "Ваш выбор: ";
        (cin >> choice).get();


        if (choice == 1)
        {
            string userName;

            cout << "Введите имя пользователя: ";
            getline(cin, userName);

            //Проходимся по контейнеру set и выводим сообщения нужного пользователя
            for (const Message& message : messages)
            {
                if (message.getUserName() == userName)
                    cout << message.getUserName() << " " << message.getTime() << ": " << message.getMessage() << endl;
            }
        }
        else if (choice == 2)
        {
            string userName;

            cout << "Введите имя пользователя: ";
            getline(cin, userName);

            string startTime, endTime;

            cout << "Введите первое время в формате (12:34:56.789): ";
            getline(cin, startTime);

            cout << "Введите второе время в формате (12:34:56.789): ";
            getline(cin, endTime);

            for (const Message& message : messages)
            {
                if (message.getUserName() == userName)
                {
                    if (message.getTime() >= startTime && message.getTime() <= endTime)
                        cout << message.getUserName() << " " << message.getTime() << ": " << message.getMessage() << endl;
                }
            }
        }
        else if (choice == 3)
        {
            string startTime, endTime;

            cout << "Введите первое время в формате (12:34:56.789): ";
            getline(cin, startTime);

            cout << "Введите второе время в формате (12:34:56.789): ";
            getline(cin, endTime);

            for (const Message& message : messages)
            {
                if (message.getTime() >= startTime && message.getTime() <= endTime)
                    cout << message.getUserName() << " " << message.getTime() << ": " << message.getMessage() << endl;
            }
        }
        else if (choice == 4)
        {
            string messageText;

            cout << "Введите сообщение: ";
            getline(cin, messageText);

            for (const Message& message : messages)
            {
                if (message.getMessage() == messageText)
                {
                    messages.erase(message);
                    break;
                }
            }
        }
        else if (choice == 5)
        {
            string userName;

            cout << "Введите имя пользователя: ";
            getline(cin, userName);

            set<Message>::iterator it = messages.begin();
            while (it != messages.end())
            {
                if (it->getUserName() == userName)
                    it = messages.erase(it);
                else
                    ++it;
            }
        }
        else
            cout << "Неправильный ввод." << endl;


        char answ;

        cout << "Вывести все сообщения?(Y;N): ";
        cin >> answ;

        if (answ == 'Y')
        {
            for (auto& message : messages)
            {
                std::cout << "User: " << message.getUserName() << std::endl;
                std::cout << "Time: " << message.getTime() << std::endl;
                std::cout << "Message: " << message.getMessage() << std::endl;
                std::cout << "--------------------------" << std::endl;
            }
        }

        cout << endl << "Вы хотите продолжить?(Y;N): ";
        cin >> answ;

        if (answ == 'N') flag = false;
    }
}
