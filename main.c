#include <stdio.h>   // thư viện với các hàm nhập xuất đã được định nghĩa
#include <stdbool.h> // thư viện với các định nghĩa và macro để hỗ trợ kiểu dữ liệu boolean
#include <stdlib.h>  // thư viện liên quan đến các hoạt động thực thi hệ thống và quản lý bộ nhớ (ví dụ: exit(), system(), malloc(), calloc(), realloc(), free())
#include <math.h>    // thư viện chứa các hàm toán học (pow, sqrt, acos, cos, sin)
#include <windows.h> // thư viện chứa các định nghĩa và hàm API trong windows

#define PI 3.14159265 // Hằng số PI
#define e 0.01        // Sai số cho phép nằm trong khoảng [0, 0.01]

double gocCanh[6];    // Lưu trữ thông số góc và cạnh của tam giác (AB, BC, CA, goc A, B, C)
double duongCao[3];   // Lưu trữ thông số đường cao từ các đỉnh của tam giác (A,B,C)
double dienTich;      // Lưu trữ thông số diện tích tam giác
double trungTuyen[3]; // Lưu trữ thông số các đường trung tuyến từ các đỉnh của tam giác (A,B,C)
double trongTam[2];   // Lưu trữ tọa độ trọng tâm của tam giác

double doDaiCanh(char diemDau, char diemCuoi, char diem[], double toado[]); // Tính toán độ dài cạnh giữa 2 điểm
void nhapToaDoDiem(char diem[], double toado[]);                            // Hàm nhập tọa độ điểm
bool kiemtra_tamgiac(char diem[], double toado[]);                          // Hàm kiểm tra tọa độ 3 điểm nhập vào có tạo thành tam giác không
void goccanh_tamgiac(char diem[], double toado[]);                          // Hàm tính toán góc, cạnh của tam giác
void xet_tamgiac(char diem[], double gocCanh[]);                            // Xác định loại tam giác (vuông, vuông cân, tù, tù cân, đều, ...)
void dientich_tamgiac(double gocCanh[]);                                    // Hàm tính diện tích tam giác
void duongcao_tamgiac(char diem[], double gocCanh[]);                       // Hàm tính đường cao tam giác
void trungtuyen_tamgiac(char diem[], double gocCanh[]);                     // Hàm tính đường trung tuyến tam giác
void tam_tamgiac(double toado[]);                                           // Hàm xác định tọa độ trọng tâm tam giác
void giaima_tamgiac(char diem[], double gocCanh[], double toado[]);         // Hàm chung gộp các hàm con lại

int main()
{
    double toado[6];                // Lưu trữ tọa độ Ox, Oy của 3 điểm
    char diem[3] = {'A', 'B', 'C'}; // Khai báo 3 đỉnh của một tam giác, sau này có thể tùy biến với nhập vào 3 đỉnh

    giaima_tamgiac(diem, gocCanh, toado);

    return 0;
}

void nhapToaDoDiem(char diem[], double toado[])
{
    char trucToaDo[2] = {'x', 'y'};
    for (int i = 0; i < 3; i++) // Vòng lặp chạy để nhập tọa độ cho 3 điểm A, B, C
    {
        printf("Nhap toa do diem %c: ", diem[i]);
        for (int j = 0; j < 2; j++) // Vòng lặp chạy để nhập tọa độ Ox, Oy
        {
            printf("\n%c%c:", *(diem + i), trucToaDo[j]); // In ra tọa độ x, y cần nhập theo các điểm
            scanf("%lf", &toado[2 * i + j]);              // Nhập lần lượt vào mảng tọa độ [Ax, Ay, Bx, By, Cx, Cy]
        }
    }
    for (int i = 0; i < 3; i++) // Sau khi nhập thì tạo một vòng lặp tương tự để in ra tọa độ các điểm
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0)
                printf("\nToa do diem %c da nhap: %c(%.2lf, %.2lf)", diem[i], diem[i], toado[2 * i + j], toado[2 * i + j + 1]);
            else
                break;
        }
    }
    printf("\n------------------------------------------------------------------");
}

double doDaiCanh(char diemDau, char diemCuoi, char diem[], double toado[]) // Hàm tính toán độ dài cạnh theo các đỉnh, sau có thể thay đổi tùy theo đỉnh nhập vào
{
    if (diemDau == diem[0] && diemCuoi == diem[1] || diemDau == diem[1] && diemCuoi == diem[0]) // tính độ dài AB
    {
        return sqrt(pow(toado[2] - toado[0], 2) + pow(toado[3] - toado[1], 2));
    }
    else if (diemDau == diem[2] && diemCuoi == diem[1] || diemDau == diem[1] && diemCuoi == diem[2]) // tính độ dài BC
    {
        return sqrt(pow(toado[4] - toado[2], 2) + pow(toado[5] - toado[3], 2));
    }
    else // tính độ dài CA
    {
        return sqrt(pow(toado[0] - toado[4], 2) + pow(toado[1] - toado[5], 2));
    }
}

bool kiemtra_tamgiac(char diem[], double toado[]) // Kiểm tra tam giác sử dụng bất đẳng thức tam giác
{
    if (doDaiCanh('A', 'B', diem, toado) + doDaiCanh('B', 'C', diem, toado) > doDaiCanh('C', 'A', diem, toado) &&
        doDaiCanh('B', 'C', diem, toado) + doDaiCanh('C', 'A', diem, toado) > doDaiCanh('A', 'B', diem, toado) &&
        doDaiCanh('C', 'A', diem, toado) + doDaiCanh('A', 'B', diem, toado) > doDaiCanh('B', 'C', diem, toado))
    {
        printf("\nToa do 3 diem nhap vao tao thanh mot tam giac\n\n");
        return true;
    }
    else
    {
        printf("\nToa do 3 diem nhap vao khong tao thanh 1 tam giac\n\n");
        Sleep(3000); // dừng lại 3s để quan sát dòng thông báo in ra
        return false;
    }
}

void goccanh_tamgiac(char diem[], double toado[]) // tính góc và cạnh tam giác dựa vào tọa độ đã cho
{
    double val;
    val = 180.0 / PI;
    printf("\n1. So do co ban cua tam giac:");
    printf("\n   Chieu dai canh %c%c: %.2lf", diem[0], diem[1], gocCanh[0] = doDaiCanh('A', 'B', diem, toado)); /*sqrt(pow(toado[2] - toado[0], 2) + pow(toado[3] - toado[1], 2))*/
    printf("\n   Chieu dai canh %c%c: %.2lf", diem[1], diem[2], gocCanh[1] = doDaiCanh('B', 'C', diem, toado)); /*sqrt(pow(toado[4] - toado[2], 2) + pow(toado[5] - toado[3], 2))*/
    printf("\n   Chieu dai canh %c%c: %.2lf", diem[2], diem[0], gocCanh[2] = doDaiCanh('C', 'A', diem, toado)); /*sqrt(pow(toado[0] - toado[4], 2) + pow(toado[1] - toado[5], 2))*/
    printf("\n   Goc %c: %.2f", diem[0], gocCanh[3] = (acos(((toado[2] - toado[0]) * (toado[4] - toado[0]) + (toado[3] - toado[1]) * (toado[5] - toado[1])) / (gocCanh[0] * gocCanh[2]))) * val);
    printf("\n   Goc %c: %.2f", diem[1], gocCanh[4] = (acos(((toado[0] - toado[2]) * (toado[4] - toado[2]) + (toado[1] - toado[3]) * (toado[5] - toado[3])) / (gocCanh[0] * gocCanh[1]))) * val);
    printf("\n   Goc %c: %.2f", diem[2], gocCanh[5] = (acos(((toado[0] - toado[4]) * (toado[2] - toado[4]) + (toado[1] - toado[5]) * (toado[3] - toado[5])) / (gocCanh[2] * gocCanh[1]))) * val);
}

void xet_tamgiac(char diem[], double gocCanh[])
{
    double gocMax = 0;
    int i, temp;
    for (i = 3; i < 6; i++)
        gocMax < gocCanh[i] ? gocMax = gocCanh[i], temp = i : gocMax;

    if (fabs(gocMax - 90) <= e) // Xác định tam giác có vuông không với góc lớn nhất có = 90 độ không và sai số cho phép là [0, 0.01]
    {
        if (fabs(gocCanh[0] - gocCanh[1]) <= e || fabs(gocCanh[1] - gocCanh[2]) <= e || fabs(gocCanh[2] - gocCanh[0]) <= e)
            printf("\n\nTam giac ABC la tam giac vuong can tai dinh %c", diem[temp - 3]); // nếu có các cặp cạnh bằng nhau thì tam giác vuông này đồng thời cũng cân với sai số cho phép là [0, 0.01]
        else
            printf("\n\nTam giac ABC la tam giac vuong tai dinh %c", diem[temp - 3]);
    }
    else if (gocMax - 90 > e) // Xác định tam giác có tù không với góc lớn nhất có lớn hơn 90 độ không và phải lớn hơn 90.001
    {
        if (fabs(gocCanh[0] - gocCanh[1]) <= e || fabs(gocCanh[1] - gocCanh[2]) <= e || fabs(gocCanh[2] - gocCanh[0]) <= e) // nếu có các cặp cạnh bằng nhau thì tam giác tù này đồng thời cũng cân với sai số cho phép là [0, 0.01]
            printf("\n\nTam giac ABC la tam giac tu va can tai dinh %c", diem[temp - 3]);
        else
            printf("\n\nTam giac ABC la tam giac tu tai dinh %c", diem[temp - 3]);
    }
    else if (fabs(gocCanh[3] - 60) <= e && fabs(gocCanh[4] - 60) <= e && fabs(gocCanh[5] - 60) <= e) // Kiểm tra tam giác đều
        printf("\n\nTam giac ABC la tam giac deu");
    else // các trường hợp còn lại với góc lớn nhất nhỏ hơn 90 là tam giác nhọn
    {
        if (fabs(gocCanh[0] - gocCanh[1]) <= e)
            printf("\n\nTam giac ABC can tai %c", diem[1]);
        else if (fabs(gocCanh[1] - gocCanh[2]) <= e)
            printf("\n\nTam giac ABC can tai %c", diem[2]);
        else if (fabs(gocCanh[2] - gocCanh[0]) <= e)
            printf("\n\nTam giac ABC can tai %c", diem[0]);
        else
            printf("\n\nTam giac ABC la tam giac nhon binh thuong");
    }
}

void dientich_tamgiac(double gocCanh[]) // hàm tính diện tích tam giác
{
    printf("\n\n2. Dien tich tam giac ABC la: %.2lf", dienTich = (gocCanh[0] * gocCanh[1] * sin(gocCanh[4] * PI / 180.0)) / 2);
}

void duongcao_tamgiac(char diem[], double gocCanh[]) // hàm tính đường cao tam giác dựa vào công thức diện tích
{
    printf("\n\n3. So do nang cao tam giac %c%c%c", diem[0], diem[1], diem[2]);
    printf("\nDo dai duong cao tu dinh %c: %.2lf", diem[0], duongCao[0] = (2 * dienTich) / gocCanh[1]);
    printf("\nDo dai duong cao tu dinh %c: %.2lf", diem[1], duongCao[1] = (2 * dienTich) / gocCanh[2]);
    printf("\nDo dai duong cao tu dinh %c: %.2lf", diem[2], duongCao[2] = (2 * dienTich) / gocCanh[0]);
}

void trungtuyen_tamgiac(char diem[], double gocCanh[]) // hàm tính đường trung tuyến tam giác dựa vào công thức cosin
{
    printf("\nDo dai trung tuyen tu dinh %c: %.2lf", diem[0], trungTuyen[0] = sqrt((2 * (pow(gocCanh[0], 2) + pow(gocCanh[2], 2)) - pow(gocCanh[1], 2)) / 4));
    printf("\nDo dai trung tuyen tu dinh %c: %.2lf", diem[1], trungTuyen[1] = sqrt((2 * (pow(gocCanh[0], 2) + pow(gocCanh[1], 2)) - pow(gocCanh[2], 2)) / 4));
    printf("\nDo dai trung tuyen tu dinh %c: %.2lf", diem[2], trungTuyen[2] = sqrt((2 * (pow(gocCanh[1], 2) + pow(gocCanh[2], 2)) - pow(gocCanh[0], 2)) / 4));
}

void tam_tamgiac(double toado[]) // hàm xác định tọa độ trọng tâm tam giác
{
    printf("\n\n4. Toa do diem dac biet cua tam giac ABC");
    printf("\nToa do trong tam: [%.2lf, %.2lf]", trongTam[0] = (toado[0] + toado[2] + toado[4]) / 3, trongTam[1] = (toado[1] + toado[3] + toado[5]) / 3);
    printf("\n\n-----------------------------------------");
}

void giaima_tamgiac(char diem[], double gocCanh[], double toado[])
{
    while (true) // tạo vòng lặp để thông số nhập vào tạo thành 1 tam giác thì thôi
    {
        system("cls"); // câu lệnh xóa màn hình
        nhapToaDoDiem(diem, toado);
        if (kiemtra_tamgiac(diem, toado)) // điều kiện thoát khỏi vòng lặp là thông số nhập vào tạo thành tam giác
        {
            goccanh_tamgiac(diem, toado);
            xet_tamgiac(diem, gocCanh);
            dientich_tamgiac(gocCanh);
            duongcao_tamgiac(diem, gocCanh);
            trungtuyen_tamgiac(diem, gocCanh);
            tam_tamgiac(toado);
            break; // thoát vòng lặp
        }
    }
}