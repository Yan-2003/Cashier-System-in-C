#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

// model for cashier
typedef struct{
    int id;
    char name[60];
}cashier;
// model for products
typedef struct{
    char id[60];
    char description[60];
    int price;
    char unit[10];
}products;
//model for sales
typedef struct{
    int day;
    char month[10];
    int year;
    char id[60];
    int Qty;
    int CashierID;
    int transaction_no;
    int price;
}sales;



// this is all the function prototypes

void addCashier();
void displayUser();
void searchUser();
void addProduct();
void displayProduct(char * username, int userID);
void searchProduct();
void login();
void menu(char * useranme, int userID);
void transact(char * username, int userID);
int calculate(sales * arry, int size);  
void displaySalse(char * username, int userID);
void edit_delete_user();

int main(){
    char input;
    system("cls");
    printf("[1]Login\n[2]Add Cashier\n[3]Display Cashier\n[4]Search Cashier\n[5]Add Product\n[6]Search Produt\n[7]Edit/Delete Cashier\n[Esc]Exit\nEnter Command: ");
    input = getch();
    switch (input){

        case '1': login(); break;

        case '2': addCashier(); break;

        case '3': displayUser(); break;
        case '4': searchUser(); break;

        case '5': addProduct(); break;

        case '6': searchProduct(); break;

        case '7': edit_delete_user(); break;

        case 27: system("cls"); exit(1); break;

        default: main(); break;

    }
    return 0;
}
// this is a fucntion to add a cashier to the database
void addCashier(){

    cashier users;
    FILE * user = fopen("user.dat", "a");

    system("cls");
    printf("Enter id:");
    scanf("%d", &users.id);
    printf("Enter name:");
    scanf(" %[^[\n]", users.name);
    fprintf(user, "%d %s\n", users.id, users.name);
    fclose(user);
    main();
}

// this will display all user Cashier
void displayUser(){
    char input;
    cashier users;
    FILE * user = fopen("user.dat", "r");
    system("cls");
    printf("\tCashiers\n");
    if(user != NULL){

        while (fscanf(user,"%d %s\n", &users.id, users.name) != EOF){
            printf("ID: %d\tName: %s\n", users.id, users.name);
        }

    }else{
        
        printf("No Cashiers has been created.\n");
    
    }
    printf("Enter to back: ");
    input = getch();
    main();
    fclose(user);
}
// this will search a user Cashier in ID
void searchUser(){
    int id;
    char input;
    cashier users;
    FILE * user = fopen("user.dat", "r");
    system("cls");
    printf("Enter id: ");
    scanf("%d", &id);
    printf("\tSearch\n");
    while (fscanf(user,"%d %s\n", &users.id, users.name) != EOF){
        if(id == users.id){
            printf("ID: %d\tName: %s\n", users.id, users.name);
        }
    }
    printf("Enter anyting to back: ");
    input = getch();
    main();
    fclose(user);
}

// this function will add Products to the data base
void addProduct(){
    char input;
    system("cls");
    products item;
    printf("Enter Product id:");
    scanf(" %[^[\n]", item.id);
    printf("Enter Product Description: ");
    scanf(" %[^[\n]", item.description);
    printf("Enter Product Price: ");
    scanf("%d", &item.price);
    printf("Enter Product Unit: ");
    scanf(" %[^[\n]", item.unit);
    FILE * items = fopen("products.dat", "a");
    fprintf(items, "%s %s %d %s\n", item.id,item.description,item.price,item.unit);
    fclose(items);
    printf("Enter '1' to add more products or any to exit: ");
    input = getch();
    if(input == '1'){
        addProduct();
    }
    main();
}
// this function display the search product
void searchProduct(){
    char id[60];
    char input;
    products items;
    FILE * item= fopen("products.dat", "r");
    system("cls");
    printf("Enter product id: ");
    scanf("%s", id);
    printf("\tSearch Product\n");
    if(item != NULL){
        while (fscanf(item, "%s %s %d %s", items.id,items.description,&items.price,items.unit) != EOF){
            if(strcmp(id,items.id) == 0){
                printf("ID: %s\nDescription: %s\nPrice: P%d\nUnit: %s\n",items.id,items.description,items.price,items.unit);
            }
        }
    }else{
        printf("The database is Empty or not Exist\n");
    }

    printf("Enter anyting to back: ");
    input = getch();
    main();
    fclose(item);
}

// this fucntion will log the user
void login(){
    system("cls");
    cashier user;
    char username[60];
    printf("Enter Name:");
    scanf("%s", username);
    FILE * users = fopen("user.dat", "r");
        while(fscanf(users, "%d %s\n", &user.id, user.name) != EOF){
            if(strcmp(username, user.name) == 0){
                fclose(users);
                menu(username, user.id);
            }
        }
    system("cls");
    printf("No user found\nEnter anything to go back: ");
    getch();
    fclose(users);
    login();
}
// this will display all the sales
void displaySalse(char * username, int userID){
    char input;
    sales sale;
    FILE * sales = fopen("sales_record.txt", "r");
    system("cls");
    printf("\t Products\n");
    if(sales != NULL){
        while (fscanf(sales, "%s %d %d %s %d %d %d\n", sale.month, &sale.day, &sale.year, sale.id, &sale.CashierID, &sale.Qty, &sale.transaction_no) != EOF){
            printf("Date:%s-%d-%d\tProductID:  %s\tQuantity:  %d\tCashierID:  %d\tTransactionNO:  %d\n", sale.month, sale.day, sale.year, sale.id, sale.CashierID, sale.Qty, sale.transaction_no);
        }
    }else{
        printf("No salse has been recorded.");
    }
    printf("\nEnter anyting to back: ");
    input = getch();
    menu(username, userID);
    fclose(sales);
}


// this will display all the product in the terminal
void displayProduct(char * username, int userID){
    char input;
    products items;
    FILE * item= fopen("products.dat", "r");
    system("cls");
    printf("\t Products\n");
    if(item != NULL){
        while (fscanf(item, "%s %s %d %s", items.id,items.description,&items.price,items.unit) != EOF){
            printf("ID: %s\tDescription: %s\tPrice: P%d\tUnit: %s\n",items.id,items.description,items.price,items.unit);
        }
    }else{
        printf("The database is Empty or not Exist");
    }

    printf("Enter anyting to back: ");
    input = getch();
    menu(username, userID);
    fclose(item);
}


// this will diplay the menu when the user is successfully log in 
void menu(char * username, int userID){
    char ch;

    system("cls");
    printf("\tWeclome Cashier %s\n", username);
    printf("[1]Add Transaction\n[2]Display Sales Record\n[3]Display Product\n[4]Delete Sale Record\n[Esc]Logout\nEnter Command: ");
    ch = getch();
    switch(ch){
        case '1':
            transact(username, userID);
            break;
        case '2':
            displaySalse(username, userID);
            break;
        case '3':
            displayProduct(username , userID);
        case '4':
            system("cls");
            if(remove("sales_record.txt") == 0){
                printf("Sales Successfully Deleted\n\nEnter anything to go back: ");
            }else{
                printf("Sales Failed to Delete it must been deleted or no reconrd of sales has been done.\n\nEnter anything to go back: ");
            }
            getch();
            menu(username, userID);
        case 27:
            main();
            break;
        default:
            menu(username, userID);
            break;
    }
}

// this will create a transaction
void transact(char * username, int userID){

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    char month_in_string[12][60] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    int sales_index = 0;
    sales * buy = malloc(sizeof(sales));
    
    int numbers_of_items = 0;
    products * arry_of_items = malloc(sizeof(products));
    

    srand(time(0));
    int random_int = rand();

    int input_product_no;
    int input_quantity_no;
   
    int item_remove;
    
    char input;

    int total = 0; 

    
    system("cls");
    FILE * items = fopen("products.dat", "r");
    while(fscanf(items," %s %s %d %s\n", 
    &arry_of_items[numbers_of_items].id,
    &arry_of_items[numbers_of_items].description, 
    &arry_of_items[numbers_of_items].price, 
    &arry_of_items[numbers_of_items].unit) != EOF){
    
        numbers_of_items++;
        if(numbers_of_items > 0){
            arry_of_items = realloc(arry_of_items, sizeof(products) * (numbers_of_items+1));
        }
    }
    fclose(items);




    menu_flag:
    system("cls");
    printf("slase index: %d\n", sales_index);
    if( sales_index > 0){
        for(int i = 0; i < sales_index; i++){
            printf("ProductID: %s\tProduct Price: P%d\tProduct Quantity: %d\n", buy[i].id, buy[i].price, buy[i].Qty);
        }
        total = calculate(buy,sales_index);
    }else{
        printf("No Record\n");
    }
    printf("\nCurrent total: %d\n", total);

    printf("\n[Esc]Return\n[1]Add Item\n[2]Remove Item\n[3]Checkout Item\nEnter Command: ");
    input = getch();
    switch(input){
        case '1':  
            system("cls");
            printf("\nthis is size of number of items: %d\n", numbers_of_items);
            printf("ProductID\tPrice\tUnit\n");
            for(int i = 0; i < numbers_of_items; i++){
                printf("[%d] %s\tP%d\t%s\n", i+1, arry_of_items[i].id, arry_of_items[i].price, arry_of_items[i].unit);
            }
            printf("Enter a product no.: ");
            scanf("%d", &input_product_no);
            printf("Enter Quantity: ");
            scanf("%d", &input_quantity_no);
            system("cls");
            if(input_product_no > numbers_of_items){
                goto menu_flag;
                break;
            }
            
            strcpy(buy[sales_index].id, arry_of_items[input_product_no-1].id);
            strcpy(buy[sales_index].month, month_in_string[tm.tm_mon]);
            buy[sales_index].day = tm.tm_mday;
            buy[sales_index].year = tm.tm_year+1900;
            buy[sales_index].CashierID = userID;
            buy[sales_index].transaction_no = random_int;
            buy[sales_index].Qty = input_quantity_no;
            buy[sales_index].price = arry_of_items[input_product_no-1].price;
            sales_index++;
            if(sales_index > 0){
                buy = realloc(buy,sizeof(sales) * (sales_index + 1));
            }
            
            goto menu_flag;
            break;
        case '2':
            
            system("cls");
            if( sales_index > 0){
                for(int i = 0; i < sales_index; i++){
                    printf("[%d] ProductID: %s\tProduct Price: P%d\tProduct Quantity: %d\n", i+1 ,buy[i].id, buy[i].price, buy[i].Qty);
                }
            }
            printf("Enter the number of the item to removed: ");
            scanf("%d", &item_remove);
            if(sales_index <= 1){
                free(buy);
                sales_index--;
                goto menu_flag;
            }
            for(int i = 0; i < sales_index; i++){
                if(i == item_remove-1){
                    buy[i].price = buy[i+1].price;
                    buy[i].Qty = buy[i+1].Qty;
                    strcpy(buy[i].id, buy[i+1].id);
                }
            }
            sales_index--;
            goto menu_flag;
            break;
        case '3':
            system("cls");
            if(total > 0){
                FILE * record_sales = fopen("sales_record.txt", "a");
                for(int i = 0; i < sales_index; i++){
                    fprintf(record_sales, "%s %d %d %s %d %d %d\n",
                    buy[i].month,
                    buy[i].day,
                    buy[i].year,
                    buy[i].id,
                    buy[i].Qty,
                    buy[i].CashierID,
                    buy[i].transaction_no
                    );
                }
                fclose(record_sales);
                printf("\tYour Receipt\n\nCashierID: %d\n",userID);
                for(int i = 0; i < sales_index; i++){
                    printf("\tProductID: %s\t----------\tP%d Qty: %d\n", buy[i].id, buy[i].price, buy[i].Qty);
                }
                printf("\nYour Transaction no.: %d\nTotal to pay: P%d\n\nEnter anything to go back:",random_int,total);
                getch();
                free(buy);
                free(arry_of_items);
                menu(username, userID);
            }else{
                printf("There is no added items please select an item first: ");
                getch();
                free(buy);
                free(arry_of_items);
                menu(username, userID);
            }
            break;
        case 27:
            free(buy);
            free(arry_of_items);
            menu(username, userID);
        default:
            free(buy);
            free(arry_of_items);
            menu(username, userID);
            break;
    }
}

// this will calculate and return the sales overall total 
int calculate(sales * arry, int size){
    int total = 0;
    for(int i = 0; i < size; i++){
        total = total + (arry[i].price * arry[i].Qty);
    }
    return total;
}


// this will edit and delete users id and name 
void edit_delete_user(){
    cashier * users = malloc(sizeof(cashier));
    int number_of_users = 0;

    int target;

    char input;
    char select;
    FILE * users_database = fopen("user.dat", "r");
    while(fscanf(users_database, "%d %s", &users[number_of_users].id, users[number_of_users].name) != EOF){
        number_of_users++;
        users = realloc(users, sizeof(cashier) * (number_of_users + 1));
    }
    fclose(users_database);

    system("cls");
    printf("\tCashiers\n\n");

    for(int i = 0; i < number_of_users; i++){
        printf("[%d] CashiersID: %d CashiersName: %s\n",i+1, users[i].id, users[i].name);
    }
    printf("\nClick 'e' to select user or anything to Exit:");
    select = getch();
    if(select != 'e'){
        main();
    }
    printf("\nEnter the number to Modify: ");
    scanf("%d", &target);

    to_edit_delete:
    system("cls");

    for(int i = 0; i < number_of_users; i++){
        if(target-1 == i){
            printf("[%d] CashiersID: %d CashiersName: %s\n",i+1, users[i].id, users[i].name);
        }
        
    }
    printf("\n[1]Update Cashier\n[2]Delete Cashier\n[Esc]Return\nEnter command: ");
    input = getch();
    
    switch(input){
        case '1': 
            system("cls");
            for(int i = 0; i < number_of_users; i++){
                if(target-1 == i){
                    printf("Edit--CashiersID: %d CashiersName: %s\n", users[i].id, users[i].name);
                }
            }
            printf("Enter new ID: ");
            scanf("%d", &users[target-1].id);
            printf("Enter new Name: ");
            scanf("%s", users[target-1].name);
            
            system("cls");            
            
            FILE * update_users = fopen("user.dat", "w");
            for(int i = 0; i < number_of_users; i++){
                fprintf(update_users, "%d %s\n", users[i].id, users[i].name);
            }
            fclose(update_users);

            printf("Cashier is successfully Updated.\nEnter anything to go back: ");
            getch();
            free(users);
            edit_delete_user();
            break;
        case '2':
            system("cls");

            for(int i = 0; i < number_of_users; i++){
                if(target-1 == i){
                    printf("Delete--CashiersID: %d CashiersName: %s\n", users[i].id, users[i].name);
                }
            }

            FILE * to_delete_a_users = fopen("user.dat", "w");
            for(int i = 0; i < number_of_users; i++){
                if(users[i].id != users[target-1].id){
                    fprintf(to_delete_a_users, "%d %s\n", users[i].id, users[i].name);
                }
            }
            fclose(to_delete_a_users);
            printf("Cashier is successfully Deleted.\nEnter anything to go back: ");
            getch();
            free(users);
            edit_delete_user();
            break;

        case 27: edit_delete_user(); break;
    
        default: goto to_edit_delete; break;
    }  
    

}
