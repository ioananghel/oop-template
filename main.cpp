#include <iostream>
#include <cstring>
#include <string>

/*
    Simulare Catalog Virtual:
    -exista optiunea de a-ti creea un cont, din care ai acces la propriile date
    -exista contul administratorului, care are drepturi de editare a datelor din catalog:
        -user: Admin01
        -pass: Admin01
    -
*/
///while in main, cu persoana logata si while in run cu actiunile propriu zise
///de implementat legatura dintre un cont si locul sau din catalog
#define MAX_SIZE 100

class Account
{
    char *user, *pass; ///datele referitoare la numele userului si la parola acestuia
    ///aceste date sunt by default private.
public:
    Account()
    {

    }
    Account(const char *user_name, const char *password) ///constructor
    {
        user = new char[strlen(user_name) + 1];
        pass = new char[strlen(password) + 1];

        //std :: cout << "In constructor, avem:" << user_name << " " << password;

        strcpy(user, user_name);
        strcpy(pass, password);

    }

    Account(const Account &a)
    {
        this -> user = new char[strlen(a.user) + 1];
        this -> pass = new char[strlen(a.pass) + 1];

        strcpy(this -> user, a.user);
        strcpy(this -> pass, a.pass);
    }

    Account operator=(Account &rhs)
    {
        /*if(*this != rhs)
        {
            delete[] this -> user;
            delete[] this -> pass;
        }*/

        this -> user = new char[strlen(rhs.user) + 1];
        this -> pass = new char[strlen(rhs.pass) + 1];

        strcpy(this -> user, rhs.user);
        strcpy(this -> pass, rhs.pass);

        std :: cout << "IN SUPERSCRIERE =: " << this -> user << " " << this -> pass;

        return *this;
    }

    bool operator==(const Account &rhs) ///operator - keyword ==> modificam asa diferite metode de comp
    {
        return (pass == rhs.pass) && (strcmp(user, rhs.user) == 0);
    }
    bool operator!=(const Account &rhs) ///operator de != <==> practic opusul lui ==
    {
        return !(*this == rhs);
    }

    const char* get_user() const;
    const char* get_pass() const;
    void change_pass();

    ~Account()
    {
        std :: cout << " hereeee\n";
        delete[] user;
        delete[] pass;
    }
};

class Student
{
    char *name;
    int *grades, index;     ///these are all private, by default

public:
    Student(const char *name_buff)      ///fiecare student va avea maxim 4 note(colocviu + examen final + *seminar + *laborator
    {                                   ///vom presupune ca toate notele au ponderi egale
        delete[] name;
        name = new char[strlen(name_buff) + 1];
        grades = new int[4];
        index = 0;

        strcpy(name, name_buff);
    }
    Student()
    {
        name = new char[5];
        strcpy(name, "null");
    }

    void get_grades();
    const char* get_name();
    void add_grades(int *v, int no);
    void change_name(const char *buff_name);

    ~Student()
    {
        delete[] name;
        delete[] grades;
    }
}studs[MAX_SIZE];

const char* Account :: get_user() const
{
    return user;
}

const char* Account ::get_pass() const
{
    return pass;
}

const char* Student :: get_name()
{
    return  this -> name;
}

void Student ::change_name(const char *buff_name)
{
    delete[] name;
    name = new char[strlen(buff_name) + 1];

    strcpy(name, buff_name);
    grades = new int[4];
}

void Student ::add_grades(int *v, int no)
{
    for(int i = 0; i < no; i++)
    {
        grades[index++] = v[i];
    }
}

void Student ::get_grades()
{
    for(int i = 0; i < index; i++)
    {
        std :: cout << grades[i] << " ";
    }
}

void admin_log_in()
{
    std :: cout << "Bine ati venit, Admin01";

    while(1)
    {
        std :: cout << "Ce actiune ati dori sa urmati?\n1. Adaugare Student\n2. Adaugare Note\n3. Afisare Note\n4. Log Out";
        fflush(stdin);

        int action;
        std :: cin >> action;

        switch(action) {
            case 1:
            {
                char buff_name[20];
                std::cout << "Intoduceti numele studentului (Prenume + Nume):";
                fflush(stdin);
                std::cin.getline(buff_name, 20);

                int last_unused = 0;
                while (strcmp(studs[last_unused].get_name(), "null"))
                    last_unused++;

                studs[last_unused].change_name(buff_name);
                std::cout << "Success: " << studs[last_unused].get_name();
                break;
            }
            case 2:
            {
                std::cout << "Introduceti numele studentului pentru care aplicati modificarea: \n";
                fflush(stdin);

                char buff_name[20];
                std::cin.getline(buff_name, 20);

                int index = 0;
                char buff_cmp[20];
                strcpy(buff_cmp, studs[index].get_name());
                while (strcmp(buff_cmp, buff_name) && index < MAX_SIZE)
                {
                    //std::cout << "BROTHERRR";
                    strcpy(buff_cmp, studs[++index].get_name());
                }

                std::cout << index << " Introduceti numarul de note pe care vreti sa le introduceti si pe acestea: \n";
                fflush(stdin);

                int nr, v[4];
                std::cin >> nr;
                for (int i = 0; i < nr; i++) {
                    std::cin >> v[i];
                }

                studs[index].add_grades(v, nr);

                break;
            }
            case 3:
            {
                std :: cout << "Introduceti numele studentului pentru care vreti sa vizualizati notele: \n";
                fflush(stdin);

                char buff_name[20];
                std::cin.getline(buff_name, 20);

                int index = 0;
                while (strcmp(studs[index].get_name(), buff_name))
                    index++;

                studs[index].get_grades();
                break;
            }
            case 4:
                return;
            default:
                std :: cout << "Alegeti una dintre optiunile afisate!";
                break;
        }
    }
}

void logged_in(Account a)
{
    char buff_name[20];
    strcpy(buff_name, a.get_user());
    std :: cout << "Bine ai venit, " << a.get_user() << "!\n";
    int index = 0;
    while (strcmp(studs[index].get_name(), buff_name) && index < MAX_SIZE) {
        index++;
        std :: cout << index << " ";
    }
    while(1)
    {
        int action; ///1 - interogare note, 2 - log out
        std :: cout << "Ce actiune ai dori sa urmezi:\n1. Afisare note\n2. Log out" << std :: endl;

        std :: cin >> action;

        switch (action)
        {
            case 1:
                studs[index].get_grades();
                break;
            case 2:
                return;
            default:
                std :: cout << "Alegeti una dintre optiunile afisate!";
                break;
        }
    }
}

void log_in(Account *v, const int index)
{
    for(int i = 0; i < index; i++)
    {
        std :: cout << "DIN LOGIN: " << v[i].get_user() << v[i].get_pass() << "\n";
    }

    char buff_name[20], buff_pass[20];

    std :: cout << "Buna ziua! Pentru a va putea conecta, va rugam sa va introduceti numele complet(prenume + nume): " << std :: endl;
    //std :: cin >> buff_name;
    fflush(stdin);
    std :: cin.getline(buff_name, 20);

    std :: cout << "Introduceti parola: " << std :: endl;
    std :: cin >> buff_pass;

    if(!strcmp(buff_name, "Admin01") && !strcmp(buff_pass, "Admin01"))
    {
        admin_log_in();
    }
    else
    {
        for (int i = 0; i < index; i++)
        {
            if (!strcmp(buff_name, v[i].get_user()))
            {
                if (!strcmp(buff_pass, v[i].get_pass()))
                {
                    logged_in(v[i]);
                    return;
                }
                else
                {
                    std::cout << "Parola introdusa este gresita!";
                    return;
                }
            }
        }
    }x
    std :: cout << "Nu aveti un cont creat!";
}

int main()
{
    Account *v;

    int index = 0;
    v = new Account[MAX_SIZE];

    std :: cout << "=======Catalog Virtual=======\n";
    while(1)
    {
        int action;
        std::cout << "\nCe actiune ati dori sa urmati:\n1. Login\t2. Creeare cont\t3. Exit" << std::endl;
        std :: cin >> action;

        switch(action) {
            case 1:
                log_in(v, index);
                break;
            case 2: {
                char buff[20];                                      ///buffer pentru citirea datelor
                char *first_name, *last_name, *pass;
                std::cout << "Introduceti prenumele: ";             ///citirea prenumelui
                fflush(stdin);
                std::cin >> buff;
                first_name = new char[strlen(buff) + 1];
                strcpy(first_name, buff);

                std::cout << std::endl << "Introduceti numele: "; ///citirea numelui
                fflush(stdin);
                std::cin >> buff;
                last_name = new char[strlen(buff) + 1];
                strcpy(last_name, buff);

                std::cout << "\nIntroduceti o parola: ";            ///setarea parolei
                fflush(stdin);
                std::cin >> buff;
                pass = new char[strlen(buff) + 1];
                strcpy(pass, buff);

                Account a(strcat(strcat(first_name, " "), last_name), pass);   ///crearea contului

                v[index++] = a;                                     ///adaugarea contului intr-un vector de conturi
                std::cout << a.get_user() << a.get_pass();
                std::cout << "De ce, frate?" << first_name << " " << last_name << " " << pass << std::endl;
                std::cout << "TEST: " << a.get_user() << " " << a.get_pass();
                for (int i = 0; i < index; i++)
                    std::cout << "\n DIN V " << v[i].get_user() << " " << v[i].get_pass() << "\n";
                break;
            }
            case 3:
                delete[] v;
                return 0;
            default:
                std::cout << "Alegeti una din variantele afisate!\n";
                break;
        }
    }

    return 0;
}