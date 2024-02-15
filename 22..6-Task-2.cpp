#include <iostream>
#include <string>
#include <map>

void hello()
{
std::cout << "----- Hello! Welcome to the 'Registry' program. -----" << std::endl << std::endl;
std::cout << " - Enter your last name to register in the registry." << std::endl;
std::cout << " - Enter 'Next' to call the next person to the register." << std::endl;
std::cout << " - Enter 'L' to view list." << std::endl;
std::cout << " - Enter 'Q' to exit the program." << std::endl << std::endl;
return;
}

//Функция ввода запроса и определение его типа
std::string req_input(int &reqType)
{
    std::string str;
    bool error = false;
    do
    {
        //Сброс ошибки
        error = false;

        //Ввод строки с запросом
        std::cout << "Please enter your request: ";
        std::getline(std::cin, str);

        //Проверка запроса на просмотр записей списка
        if (str == "Next")
        {
            reqType=2;
            return str;
        }        
        
        //Проверка запроса на просмотр записей списка
        if (str == "L")
        {
            reqType=3;
            return str;
        }
        
        //Проверка запроса на выход из программы
        if (str == "Q")
        {
            reqType=4;
            return str;
        }
        
        //Проверка ввода фамилии
        if (str.length()>0 & isupper(str[0]))
        {
            for (int i=1; i<str.length(); i++)
            {
                if (!isalpha(str[i]))
                {
                    error = true;
                    i = str.length() - 1;
                }
            }
            if (!error) //Если запрос прошел проверку, то вернуть код запроса - 1, если нет выдать сообщение об ошибке
            {
                reqType=1;
                return str;
            } 
            else 
            {
                std::cerr << "Error when entering last name! Repeat input." << std::endl;
            } 
        }
        else
        {
            error = true;
            std::cerr << "Error when entering last name! Repeat input." << std::endl;
        }
    } while (error);

    return str;
}

//Функция добавления в список
void add_to_list (std::map<std::string, std::string> &list, std::string &name)
{
    char n = '0';
    std::string key;

    //Создание уникального ключа
    do
    {
        key = name +'#' + n;
        n++;
    } 
    while (list.count(key));

    //Запись в список
    list[key] = name;
        
    std::cout << std::endl;
    std::cout << "<- " << name << std::endl;
    std::cout << std::endl;
    
    return;
}

//Функция вызова первого по списку в алфавитном порядке
void call (std::map<std::string, std::string> &list)
{
    std::cout << std::endl;

    //Проверка наличия записей в списке
    if (list.empty())
    {
        std::cerr << "The list is empty!" << std::endl << std::endl;
        return;
    }
    //Вызов первого в списке и удаление его из списка
    else
    {
        std::cout << "-> " << list.begin()->second << std::endl << std::endl;
        list.erase(list.begin()); 
        return;
    }
}

//Функция просмотра записей в списке
void view_list (std::map<std::string, std::string> &list)
{
    std::cout << std::endl;

    //Проверка наличия записей в списке
    if (list.empty())
    {
        std::cerr << "The list is empty!" << std::endl << std::endl;
        return;
    }

    std::cout << std::endl << "Key:\tLast name:" << std::endl;

    for (std::map<std::string, std::string>::iterator it=list.begin(); it != list.end(); ++it)
    {
        std::cout << it->first << "\t" << it->second << std::endl;
    }

    std::cout << std::endl;

    return;
}

int main()
{
    
    std::map<std::string, std::string> list;

    hello();

    int reqType = 0; //Переменная с кодом запроса

    std::string request;

    do
    {
        request = req_input(reqType);
        if (reqType == 1) add_to_list (list, request);
        if (reqType == 2) call (list);
        if (reqType == 3) view_list (list);
    } while (reqType!=4);
    
    std::cout << std::endl << "Program completed. Press any key...";
    std::cin.get();

    return 0;
}