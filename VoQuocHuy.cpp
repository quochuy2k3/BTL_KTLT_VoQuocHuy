#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <stdlib.h>
#include <curses.h>
#define getch() wgetch(stdscr)
using namespace std;
struct user
{
    string id;
    string tk;
    string mk;
    string vaitro;
};
struct item
{
    string maDinhDanh;
    string mainItem;
    string model;
    string name;
    double price;
};
int CountLine(string file)
{
    ifstream inData;
    string s;
    int count = 0;
    inData.open(file);
    if (inData.is_open())
    {
        while (!inData.eof())
        {
            getline(inData, s);
            if (s == "")
                break;
            {
                count++;
            }
        }
        inData.close();
        return count;
    }
    else
        return 0;
}
void Data(user ds, string file)
{
    ofstream outFile;
    outFile.open(file, ios::app);
    if (outFile.is_open())
    {
        outFile << ds.id << "#";
        outFile << ds.tk << "#";
        outFile << ds.mk << "#";
        outFile << ds.vaitro << endl;

        outFile.close();
        cout << "Ghi file thanh cong!" << endl;
    }
}
void Data(item *ds, const int n, string file)
{
    ofstream outFile;
    outFile.open(file, ios::app);
    if (outFile.is_open())
    {
        for (int i = 0; i < n; i++)
        {
            outFile << ds[i].maDinhDanh << "#";
            outFile << ds[i].mainItem << "#";
            outFile << ds[i].model << "#";
            outFile << ds[i].name << "#";
            outFile << ds[i].price << endl;
        }
        outFile.close();
        cout << "Ghi file thanh cong!" << endl;
    }
}
bool CheckCode(item *dsCheck, string CodeCheck, int n)
{

    for (int i = 0; i < n; i++)
    {
        if (dsCheck[i].maDinhDanh.compare(CodeCheck) == 0)
            return true;
        else
            return false;
    }
}
bool CheckID(user *ds, string id, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (ds[i].id == id)
        {
            return true;
        }
    }
    return false;
}
void importData(item *&ds, item *listToCheck, int n)
{
    int numIn;
    do
    {
        cout << "Nhap so luong san pham muon nhap: ";
        cin >> numIn;
        cin.ignore();
        if (!cin.good())
        {
            cout << "Nhap sai! Hay nhap so \n";
        }
        else if (numIn <= 0 || numIn >= 1000)
            cout << "Nhap sai! Hay nhap so nguyen duong nho hon 1000. \n";
    } while (!cin.good() || (numIn <= 0 || numIn >= 1000));
    ds = new item[numIn];
    int randNum;
    srand(time(NULL));

    for (int i = 0; i < numIn; i++)
    {
        cout << "Nhap item thu [" << i + 1 << "] " << endl;
        cout << "Nhap ma san pham: ";
        getline(cin, ds[i].mainItem);
        cout << "Nhap model: ";
        getline(cin, ds[i].model);
        cout << "Nhap ten san pham: ";
        getline(cin, ds[i].name);
        cout << "Nhap gia san pham: ";
        cin >> ds[i].price;
        cin.ignore();
        do
        {
            randNum = 100 + rand() % (999 + 1 - 100);
            ds[i].maDinhDanh = "ITS" + to_string(randNum);
        } while (CheckCode(listToCheck, ds[i].maDinhDanh, n));
    }

    Data(ds, numIn, "Data.txt");

    Data(ds, numIn, "History.txt");
}
void readData(user *&ds, int &n, string file)
{
    ifstream inData;

    inData.open(file);
    if (inData.is_open())
    {
        for (int i = 0; i < n; i++)
        {
            getline(inData, ds[i].id, '#');
            getline(inData, ds[i].tk, '#');
            getline(inData, ds[i].mk, '#');
            getline(inData, ds[i].vaitro);
        }
    }
}
void readData(item *&ds, int &n, string file)
{
    ifstream inData;

    inData.open(file);
    if (inData.is_open())
    {
        for (int i = 0; i < n; i++)
        {
            getline(inData, ds[i].maDinhDanh, '#');
            getline(inData, ds[i].mainItem, '#');
            getline(inData, ds[i].model, '#');
            getline(inData, ds[i].name, '#');
            inData >> ds[i].price;
            inData.ignore();
        }
    }
    else
    {
        cout << "Khong the mo file \n";
    }
}
bool compareCode(item x, string code)
{
    if (x.maDinhDanh.compare(code) == 0)
    {
        return 1;
    }
    else
        return 0;
}
item InputToFind(item *ds, int n)
{
    string CodeIn;
    bool flag;
    do
    {
        cout << "Nhap ma dinh danh san pham : ";
        getline(cin, CodeIn);
        for (int i = 0; i < n; i++)
        {
            if (compareCode(ds[i], CodeIn))
                return ds[i];
            else
                flag = true;
        }
        if (flag)
        {
            cout << "Ma dinh danh khong ton tai. Nhap lai!" << endl;
        }
    } while (flag);
}
void displayItemS(item *ds, const int n)
{
    cout
        << "STT \t CodeItem \t Product \t Model    \t Name \t  \t \tPrice" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i + 1
             << " \t " << ds[i].maDinhDanh << " \t " << ds[i].mainItem << " \t "
             << " \t " << ds[i].model << " \t  "
             << "\t " << ds[i].name << " \t \t " << ds[i].price << endl;
    }
}
void Find(item *ds, int n)
{
    item *newIT;
    int inNum;
    do
    {
        cout << "Nhap so san pham muon tim: ";
        cin >> inNum;
        if (!cin.good())
        {
            cout << "Nhap sai! Hay nhap so \n";
        }
        else if (inNum <= 0 || inNum >= 1000)
            cout << "Nhap sai! Hay nhap so nguyen duong nho hon 1000. \n";
    } while (!cin.good() || inNum <= 0 || inNum >= 1000);
    cin.ignore();
    newIT = new item[100];
    for (int i = 0; i < inNum; i++)
    {
        newIT[i] = InputToFind(ds, n);
    }
    displayItemS(newIT, inNum);
    delete[] newIT;
    newIT = NULL;
}
void defaultFile()
{
    FILE *f = fopen("Data.txt", "w");
    if (f != NULL)
    {
        fclose(f);
        printf("- Da xoa san pham\n");
    }
    else
    {
        printf("- Mo file that bai\n");
    }
}
void xoa(item *ds, int &n, int vt)
{
    for (int i = vt; i < n; i++)
        *(ds + i) = *(ds + i + 1);
    --n;
}
item InputToFind(item *ds, int &n, int &idx)
{
    string CodeIn;
    bool flag;
    do
    {
        cout << "Nhap ma dinh danh san pham : ";
        getline(cin, CodeIn);
        for (int i = 0; i < n; i++)
        {
            if (compareCode(ds[i], CodeIn))
            {
                idx = i;
                return ds[i];
            }
            else
                flag = true;
        }
        if (flag)
        {
            cout << "Ma dinh danh khong ton tai. Nhap lai!" << endl;
        }
    } while (flag);
}
void DeletItem(item *ds, int n)
{
    item *newRemove;
    newRemove = new item[1];
    int indexRM;
    newRemove[0] = InputToFind(ds, n, indexRM);
    xoa(ds, n, indexRM);
    defaultFile();
    Data(ds, n, "Data.txt");
    Data(newRemove, 1, "History.txt");
    delete[] newRemove;
}
int numKT()
{
    int inNum;
    do
    {
        cout << "Nhap so san pham muon thuc hien: ";
        cin >> inNum;
        if (!cin.good())
        {
            cout << "Nhap sai! Hay nhap so \n";
        }
        else if (inNum <= 0 || inNum >= 1000)
            cout << "Nhap sai! Hay nhap so nguyen duong nho hon 1000. \n";
    } while (!cin.good() || inNum <= 0 || inNum >= 1000);
    cin.ignore();
    return inNum;
}
double Sum(item *ds, int sl)
{
    double sum = 0.0;
    for (int i = 0; i < sl; i++)
    {
        sum = sum + ds[i].price * 1.0;
    }
    return sum;
}
void XuatDon(item *ds, int n)
{
    int numIn = numKT();
    int idx[numIn];
    item *newRemove;
    newRemove = new item[numIn];
    for (int i = 0; i < numIn; i++)
    {
        newRemove[i] = InputToFind(ds, n, idx[i]);
        xoa(ds, n, idx[i]);
    }
    double money = Sum(newRemove, numIn);
    defaultFile();
    Data(ds, n, "Data.txt");
    Data(newRemove, numIn, "History.txt");
    displayItemS(newRemove, numIn);
    cout << "Tong tien la: " << money << endl;
    delete[] newRemove;
}
void TTT(item *ds, const int n)
{
    item tmp;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            if (ds[i].price > ds[j].price)
            {
                tmp = ds[i];
                ds[i] = ds[j];
                ds[j] = tmp;
            }
        }
}
void increase(item *ds, const int n)
{
    TTT(ds, n);
    displayItemS(ds, n);
}
void decrease(item *ds, const int n)
{
    TTT(ds, n);
    cout
        << "STT \t CodeItem \t Product \t Model    \t Name \t  \t \tPrice" << endl;
    for (int i = n - 1; i >= 0; i--)
    {
        cout << n - i
             << " \t " << ds[i].maDinhDanh << " \t " << ds[i].mainItem << " \t "
             << " \t " << ds[i].model << " \t  "
             << "\t " << ds[i].name << " \t \t " << ds[i].price << endl;
    }
}
bool compareInfor(item x, string code)
{
    if (x.mainItem.compare(code) == 0)
    {
        return 1;
    }
    else
        return 0;
}
void maItem(item *ds, int n)
{
    string CodeIn;
    bool flag;
    do
    {
        cin.ignore();
        cout << "Nhap ma san pham : ";
        getline(cin, CodeIn);
        for (int i = 0; i < n; i++)
        {
            if (ds[i].mainItem.compare(CodeIn) == 0)
            {
                if (i == 0)
                {
                    cout
                        << "STT \t CodeItem \t Product \t Model    \t Name \t  \t \tPrice" << endl;
                }
                cout << i + 1
                     << " \t " << ds[i].maDinhDanh << " \t " << ds[i].mainItem << " \t "
                     << " \t " << ds[i].model << " \t  "
                     << "\t " << ds[i].name << " \t \t " << ds[i].price << endl;
            }
            else
                flag = true;
        }
        if (!flag)
        {
            cout << "Ma dinh danh khong ton tai. Nhap lai!" << endl;
        }
    } while (!flag);
}
void menuKH()
{
    cout << "1. Xem danh sach tat ca san pham" << endl;
    cout << "2. Xem danh sach theo gia tang" << endl;
    cout << "3. Xem danh sach theo gia giam" << endl;
    cout << "4. Xem danh sach theo ma san pham" << endl;
    cout << "5. Thoat " << endl;
    cout << "Moi ban nhap: ";
}
void menuSell()
{
    cout << "1. Xem danh sach tat ca san pham" << endl;
    cout << "2. Xem danh sach theo gia tang" << endl;
    cout << "3. Xem danh sach theo gia giam" << endl;
    cout << "4. Xem danh sach theo ma san pham" << endl;
    cout << "5. Tim kiem san pham theo ma dinh danh" << endl;
    cout << "6. Xuat don hang" << endl;
    cout << "7. Thoat " << endl;
    cout << "Moi ban nhap: ";
}
void menuQL()
{

    cout << "1. Xem danh sach tat ca san pham" << endl;
    cout << "2. Xem danh sach theo gia tang" << endl;
    cout << "3. Xem danh sach theo gia giam" << endl;
    cout << "4. Xem danh sach theo ma san pham" << endl;
    cout << "5. Tim kiem san pham theo ma dinh danh" << endl;
    cout << "6. Nhap san pham vao kho" << endl;
    cout << "7. Xoa san pham theo ma dinh danh" << endl;
    cout << "8. Xem danh sach tat ca san pham da xuat va xoa" << endl;
    cout << "9. Thoat " << endl;
    cout << "Moi ban nhap: ";
}
void menuL()
{
    cout << "1. Da co tai khoan" << endl;
    cout << "2. Tao tai khoan" << endl;
}

void signup(user *&ds, int &n, string vaitro)
{
    user u;
    bool check;
    int randNum;
    do
    {
        check = false;
        cout << "Nhap ten tai khoan: ";
        cin >> u.tk;
        cout << "Nhap mat khau: ";
        cin >> u.mk;
        u.vaitro = vaitro;
        u.id = "TK";
        string newId;
        do
        {
            randNum = 100 + rand() % (999 + 1 - 100);
            newId = "TK" + to_string(randNum);
        } while (CheckID(ds, newId, n));
        u.id = newId;
        for (int i = 0; i < n; i++)
        {
            if (ds[i].tk == u.tk)
            {
                check = true;
                break;
            }
        }
        if (check)
        {
            cout << "TK da ton tai. Nhap lai!" << endl;
        }
    } while (check);
    // ds = (user *)realloc(ds, (n + 1) * sizeof(user));
    // ds[n] = u;
    // n++;
    user *tmp = new user[n + 1];
    for (int i = 0; i < n; i++)
    {
        tmp[i] = ds[i];
    }
    tmp[n] = u;
    n++;
    Data(u, "User.txt");
    cout << "Dang ky thanh cong!" << endl;
    delete[] ds;
    ds = tmp;
    // ...
}
void login(user *ds, int n, string vaitro)
{
    string tk, mk;
    bool check = false;
    do
    {
        cout << "Nhap ten dang nhap: ";
        cin >> tk;
        cout << "Nhap mat khau: ";
        cin >> mk;
        for (int i = 0; i < n; i++)
        {
            if (ds[i].tk == tk && ds[i].mk == mk && ds[i].vaitro == vaitro)
            {
                cout << "Dang nhap thanh cong!" << endl;
                check = true;
                break;
            }
        }
        if (!check)
        {
            cout << "Dang nhap that bai. Vui long nhap lai!" << endl;
        }
    } while (!check);
}
int main()
{
    user *listU;
    item *list;
    item *listImport;
    int n = CountLine("Data.txt"); // so luong phan tu
    list = new item[n];
    int count = CountLine("User.txt"); // so luong phan tu
    listU = new user[count];
    readData(listU, count, "User.txt");
    int chon;
    system("clear");
    do
    {
        cout << "1. Khach hang" << endl;
        cout << "2. Seller" << endl;
        cout << "3. Quan ly" << endl;
        cout << "4. Thoát" << endl;
        cout << "Moi ban nhap: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
        {
            system("clear");
            int option1;
            do
            {
                menuL();
                cin >> option1;
                switch (option1)
                {
                case 1:
                    break;
                case 2:
                    count = CountLine("User.txt"); // so luong phan tu

                    signup(listU, count, "KH");
                    break;
                default:
                    break;
                }

            } while (option1 != 1);
            system("clear");
            count = CountLine("User.txt"); // so luong phan tu
            listU = new user[count];
            readData(listU, count, "User.txt");
            login(listU, count, "KH");
            cout << "Ban la khach hang" << endl;
            int option;
            do
            {
                menuKH();
                cin >> option;
                switch (option)
                {
                case 1: // DONE
                    system("clear");
                    n = CountLine("Data.txt");
                    list = new item[n];
                    readData(list, n, "Data.txt");
                    displayItemS(list, n);
                    break;
                case 2: // tang DONE
                    system("clear");
                    readData(list, n, "Data.txt");
                    increase(list, n);
                    break;
                case 3: // giam DONE
                    system("clear");
                    readData(list, n, "Data.txt");
                    decrease(list, n);
                    break;
                case 4: // sort theo ma IP SS MAC... DONE
                    system("clear");
                    readData(list, n, "Data.txt");
                    maItem(list, n);
                    break;
                case 5:
                    system("clear");
                    break;
                default:
                    cout << "Loi! " << endl;
                    break;
                }
            } while (option != 5);
            break;
        }
        case 2:
        {
            system("clear");
            int option;
            do
            {
                menuL();
                cin >> option;
                switch (option)
                {
                case 1:
                    break;
                case 2:
                    system("clear");
                    count = CountLine("User.txt"); // so luong phan tu
                    signup(listU, count, "BH");
                    break;
                default:
                    break;
                }
            } while (option != 1);
            system("clear");
            int choose;
            count = CountLine("User.txt"); // so luong phan tu
            listU = new user[count];
            readData(listU, count, "User.txt");
            login(listU, count, "BH");
            system("clear");

            do
            {
                cout << "Login thanh cong!" << endl;
                cout << "Ban la Seller" << endl;
                menuSell();
                cin >> choose;
                switch (choose)
                {
                case 1: // DONE
                    system("clear");
                    n = CountLine("Data.txt");
                    list = new item[n];
                    readData(list, n, "Data.txt");
                    displayItemS(list, n);
                    break;
                case 2: // tang DONE
                    system("clear");
                    readData(list, n, "Data.txt");
                    increase(list, n);
                    break;
                case 3: // giam DONE
                    system("clear");
                    readData(list, n, "Data.txt");
                    decrease(list, n);
                    break;
                case 4: // sort theo ma IP SS MAC... DONE
                    readData(list, n, "Data.txt");
                    maItem(list, n);
                    break;
                case 5: // Tim kiem DONE
                    system("clear");
                    readData(list, n, "Data.txt");
                    Find(list, n);
                    break;

                case 6: // Xuat hoa don
                    system("clear");
                    cin.ignore();
                    readData(list, n, "Data.txt");
                    XuatDon(list, n);
                    break;
                case 7:
                    system("clear");
                    break;
                default:
                    cout << "Loi! " << endl;
                    break;
                }
            } while (choose != 7);
            break;
        }
        case 3:
            system("clear");
            int option;
            do
            {
                menuL();
                cin >> option;
                switch (option)
                {
                case 1:
                    break;
                case 2:

                    count = CountLine("User.txt"); // so luong phan tu
                    signup(listU, count, "QL");
                    break;
                default:
                    break;
                }
            } while (option != 1);
            system("clear");

            int choose;
            count = CountLine("User.txt"); // so luong phan tu
            listU = new user[count];
            readData(listU, count, "User.txt");
            login(listU, count, "QL");
            system("clear");

            cout << "Ban la quan ly" << endl;
            int chon;
            do
            {
                menuQL();
                cin >> chon;
                switch (chon)
                {
                case 1: // DONE
                    system("clear");
                    n = CountLine("Data.txt");
                    list = new item[n];
                    readData(list, n, "Data.txt");
                    displayItemS(list, n);
                    break;
                case 2: // tang DONE
                    system("clear");
                    readData(list, n, "Data.txt");
                    increase(list, n);
                    break;
                case 3: // giam DONE
                    system("clear");
                    readData(list, n, "Data.txt");
                    decrease(list, n);
                    break;
                case 4: // sort theo ma IP SS MAC... DONE
                    readData(list, n, "Data.txt");
                    maItem(list, n);
                    break;
                case 5: // Tim kiem DONE
                    system("clear");
                    readData(list, n, "Data.txt");
                    Find(list, n);
                    break;
                case 6: // Nhap DONE
                    readData(list, n, "Data.txt");
                    importData(listImport, list, n);
                    break;
                case 7: // Xoa DONE
                    cin.ignore();
                    readData(list, n, "Data.txt");
                    DeletItem(list, n);
                    break;
                case 8: // history DONE
                    n = CountLine("History.txt");
                    list = new item[n];
                    readData(list, n, "History.txt");
                    displayItemS(list, n);
                    break;
                case 9:
                    system("clear");
                    break;
                default:
                    cout << "Loi! " << endl;
                    break;
                }
            } while (chon != 9);
            system("clear");
            break;
        case 4:
            system("clear");
            cout << "Đã thoát chương trình! " << endl;
            break;
        default:
            system("clear");
            cout << "Hãy nhập từ 1-4! " << endl;
            break;
        }
    } while (chon != 4);
    delete[] list;
    delete[] listU;
    list = 0;
    return 0;
}