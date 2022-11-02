#include <iostream>
#include <cstring>
#include <string>

/*
    Simulare Catalog Virtual:

    -exista un cont al administratorului, care creeaza catalogul propriu-zis si are drept de modificare:
        -username: Admin01
        -password: Admin01

    -in calitate de student, exista optiunea de a-ti creea un cont, din care ai acces la propriile date(read-only)

    -conturile create de studenti - class Account
    -conturile(catalogul cu note) create de Admin01 - class Student

    -class Account - contine - un username( Prenume + Nume )
                             - o parola
    -class Student - contine - un nume ( Prenume + Nume ) - acesta face legatura cu contul creat de student
                             - un vector de note si un index corespunzator acestuia
*/

/*
    +++++++++++++Pentru a testa mediul intr-un mod realist, putem urma acesti pasi:+++++++++++++

    -logare in contul de administrator, cu credentialele de mai sus;
    -adaugarea unui/mai multor student/studenti in catalog
    -adaugarea unor note pentru student/studenti
    -log-out din contul administratorului
    -crearea unui cont ( cum ar face-o un student )
    -logarea in contul unui student cu credentialele setate in pasul anterior
    -interogarea notelor
    -log-out din cont

    *-ulterior, putem sa ne mai logam din contul de administrator si sa mai facem modificari asupra notelor / sa mai adaugam elevi in catalog,
        pentru a testa mai departe functionalitatea.
*/

int MAX_SIZE;

class Account
{
    char *user = nullptr, *pass = nullptr; ///datele referitoare la numele userului si la parola acestuia
    ///aceste date sunt by default private.
public:
    Account()   ///constructor blank
    {

    }
    Account(const char *user_name, const char *password) ///constructor cu parametrii transmisi
    {
        user = new char[strlen(user_name) + 1];
        pass = new char[strlen(password) + 1];

        //std :: cout << "In constructor, avem:" << user_name << " " << password;

        strcpy(user, user_name);
        strcpy(pass, password);

    }

    Account(const Account &a)   ///constructor de copiere
    {
        this -> user = new char[strlen(a.user) + 1];
        this -> pass = new char[strlen(a.pass) + 1];

        strcpy(this -> user, a.user);
        strcpy(this -> pass, a.pass);
    }

    Account operator=(Account &rhs) ///pverloading operator =
    {
        if(*this != rhs) {
            delete[] this->user;
            delete[] this->pass;


            this->user = new char[strlen(rhs.user) + 1];
            this->pass = new char[strlen(rhs.pass) + 1];

            strcpy(this->user, rhs.user);
            strcpy(this->pass, rhs.pass);

            //std :: cout << "IN SUPERSCRIERE =: " << this -> user << " " << this -> pass;
        }
        return *this;
    }

    bool operator==(const Account &rhs) ///overloading operator ==
    {
        return (pass == rhs.pass) && (strcmp(user, rhs.user) == 0);
    }
    bool operator!=(const Account &rhs) ///overloading operator !=
    {
        return !(*this == rhs);
    }

    friend std :: istream& operator>>(std :: istream &stream, Account& a)   ///overloading operator >> pentru citire
    {
        char buff[20];                                      ///buffer pentru citirea datelor
        char *first_name, *last_name, *pass;
        std::cout << "\nIntroduceti prenumele:\n";             ///citirea prenumelui
        fflush(stdin);
        std::cin >> buff;
        first_name = new char[strlen(buff) + 1];
        strcpy(first_name, buff);

        std::cout << std::endl << "Introduceti numele:\n"; ///citirea numelui
        fflush(stdin);
        std::cin >> buff;
        last_name = new char[strlen(buff) + 1];
        strcpy(last_name, buff);

        std::cout << "Introduceti o parola:\n";            ///setarea parolei
        fflush(stdin);
        std::cin >> buff;
        pass = new char[strlen(buff) + 1];
        strcpy(pass, buff);

        a.user = new char[strlen(first_name) + strlen(last_name) + 2];
        a.pass = new char[strlen(pass) + 1];

        strcpy(a.user, strcat(strcat(first_name, " "), last_name));
        strcpy(a.pass, pass);


        return stream;
    }
    friend std :: ostream& operator<<(std :: ostream &stream, const Account& a) ///overloading operator << pentru afisare
    {
        std :: cout << a.user << " " << a.pass;

        return stream;
    }

    const char* get_user() const;
    const char* get_pass() const;
    void change_pass();

    ~Account()  ///deconstructor
    {
        //std :: cout << " hereeee\n";
        delete[] user;
        delete[] pass;
    }
};

class Student
{
    char *name;
    int *grades, index;     ///datele referitoare la numele studentului si notele sale
    ///these are all private, by default
    ///fiecare student va avea maxim 4 note(colocviu + examen final + *seminar + *laborator
    ///vom presupune ca toate notele au ponderi egale, deci nu ne va interesa care apartine carui examen

public:
    Student(const char *name_buff)  ///constructor cu numele transmis ca parametru
    {
        delete[] name;
        name = new char[strlen(name_buff) + 1];
        grades = new int[4];
        index = 0;

        strcpy(name, name_buff);
    }
    Student()   ///constructor blank
    {
        name = new char[5];
        strcpy(name, "null");
    }

    void get_grades() const;
    const char* get_name() const;
    void add_grades(int *v, int no);
    void change_name(const char *buff_name);

    ~Student()
    {
        delete[] name;
        delete[] grades;
    }
};

Student *studs;

const char* Account :: get_user() const
{
    return user;
}

const char* Account ::get_pass() const
{
    return pass;
}

const char* Student :: get_name() const
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

void Student ::get_grades() const
{
    for(int i = 0; i < index; i++)
    {
        std :: cout << grades[i] << " ";
    }
}

void admin_log_in()
{
    std :: cout << "\nBine ati venit, Admin01\n";

    while(1)
    {
        std :: cout << "\nCe actiune ati dori sa urmati?\n1. Adaugare Student\n2. Adaugare Note\n3. Afisare Note\n4. Log Out\n";
        fflush(stdin);

        int action;
        std :: cin >> action;

        switch(action) {
            case 1:
            {
                char buff_name[20];
                std::cout << "\nIntoduceti numele studentului (Prenume + Nume):\n";
                fflush(stdin);
                std::cin.getline(buff_name, 20);

                int last_unused = 0;
                while (strcmp(studs[last_unused].get_name(), "null"))
                    last_unused++;

                studs[last_unused].change_name(buff_name);
                std::cout << "\nSuccess: " << studs[last_unused].get_name() << "\n";
                break;
            }
            case 2:
            {
                std::cout << "\nIntroduceti numele studentului pentru care aplicati modificarea: \n";
                fflush(stdin);

                char buff_name[20];
                std::cin.getline(buff_name, 20);

                int index = 0;
                char buff_cmp[20];
                strcpy(buff_cmp, studs[index].get_name());
                while (strcmp(buff_cmp, buff_name) && index < MAX_SIZE - 1)
                {
                    //std::cout << "test";
                    strcpy(buff_cmp, studs[++index].get_name());
                }

                std::cout << "\nIntroduceti numarul de note pe care vreti sa le introduceti si pe acestea: \n";
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
                std :: cout << "\nIntroduceti numele studentului pentru care vreti sa vizualizati notele: \n";
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
                std :: cout << "\nAlegeti una dintre optiunile afisate!\n";
                break;
        }
    }
}

void logged_in(Account a)
{
    char buff_name[20];
    strcpy(buff_name, a.get_user());
    std :: cout << "\nBine ai venit, " << a.get_user() << "!\n";
    int index = 0;
    while (index < MAX_SIZE && strcmp(studs[index].get_name(), buff_name)) {
        index++;
        //std :: cout << index << " ";
    }
    while(1)
    {
        int action; ///1 - interogare note, 2 - log out
        std :: cout << "\nCe actiune ai dori sa urmezi:\n1. Afisare note\n2. Log out\n" << std :: endl;

        std :: cin >> action;

        switch (action)
        {
            case 1:
                studs[index].get_grades();
                break;
            case 2:
                return;
            default:
                std :: cout << "\nAlegeti una dintre optiunile afisate!\n";
                break;
        }
    }
}

void log_in(Account *v, const int index)
{
    /*for(int i = 0; i < index; i++)
    {
        std :: cout << "DIN LOGIN: " << v[i].get_user() << v[i].get_pass() << "\n";
    }*/

    char buff_name[20], buff_pass[20];

    std :: cout << "\nBuna ziua! Pentru a va putea conecta, va rugam sa va introduceti numele complet(prenume + nume): \n";
    //std :: cin >> buff_name;
    fflush(stdin);
    std :: cin.getline(buff_name, 20);

    std :: cout << "\nIntroduceti parola: " << std :: endl;
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
                    std::cout << "\nParola introdusa este gresita!\n";
                    return;
                }
            }
        }
    }
    std :: cout << "\nNu aveti un cont creat!\n";
}

int main()
{
    Account *v;

    int n;
    std :: cout << "Introduceti numarul de studenti: " << std :: endl;
    std :: cin >> MAX_SIZE;

    int index = 0;
    v = new Account[MAX_SIZE];
    studs = new Student[MAX_SIZE];

    std :: cout << "\n==========Catalog Virtual==========\n";
    while(1)
    {
        int action;
        std::cout << "\nCe actiune ati dori sa urmati:\n1. Login\n2. Creare cont\n3. Exit" << std::endl;
        std :: cin >> action;

        switch(action) {
            case 1:
                log_in(v, index);
                break;
            case 2: {
                ///portiunea comentata reprezinta citirea de dinaintea overloading-ului operatorului >>
                /*char buff[20];                                      ///buffer pentru citirea datelor
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
                */

                Account a;
                std :: cin >> a;

                v[index++] = a;    ///adaugarea contului intr-un vector de conturi

                /*std::cout << a.get_user() << a.get_pass();
                std::cout << "TEST: " << a.get_user() << " " << a.get_pass();
                for (int i = 0; i < index; i++)
                    std::cout << "\n DIN V " << v[i].get_user() << " " << v[i].get_pass() << "\n";*/
                break;
            }
            case 3:
                delete[] v;
                return 0;
            default:
                std::cout << "\nAlegeti una din variantele afisate!\n";
                break;
        }
    }

    return 0;
}