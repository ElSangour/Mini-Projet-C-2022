#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#define ps 0.5
#define VERSION "v1.0"

typedef FILE file;
typedef struct {
	unsigned int id, quantity;
	char name[100], brand[20];
	float price;
} product;

void InitializeProductsFile(void);
unsigned int GetProductsNumber(void);
int AddProduct(product);
int ModifyProduct(unsigned int, unsigned int, char*, char*, float);
int RemoveProduct(unsigned int);
product* GetProducts(unsigned int*);

void stockINi() {
	printf("\nSSSSSSSSSSSSSSS     ttttt                                                kkkkkkkk           IIIIIIIIIINNNNNNNN        NNNNNNNN  iiii\n");   
	printf(" SS:::::::::::::::S  ttt:::t                                               k::::::k           I::::::::IN:::::::N       N::::::N i::::i \n");
	printf("S:::::SSSSSS::::::S  t:::::t                                               k::::::k           I::::::::IN::::::::N      N::::::N  iiii  \n");
	printf("S:::::S     SSSSSSS  t:::::t                                               k::::::k           II::::::IIN:::::::::N     N::::::N        \n");
	printf("S:::::S        ttttttt:::::ttttttt       ooooooooooo       cccccccccccccccc k:::::k    kkkkkkk  I::::I  N::::::::::N    N::::::Niiiiiii \n");
	printf("S:::::S        t:::::::::::::::::t     oo:::::::::::oo   cc:::::::::::::::c k:::::k   k:::::k   I::::I  N:::::::::::N   N::::::Ni:::::i\n"); 
	printf(" S::::SSSS     t:::::::::::::::::t    o:::::::::::::::o c:::::::::::::::::c k:::::k  k:::::k    I::::I  N:::::::N::::N  N::::::N i::::i \n");
	printf("  SS::::::SSSSStttttt:::::::tttttt    o:::::ooooo:::::oc:::::::cccccc:::::c k:::::k k:::::k     I::::I  N::::::N N::::N N::::::N i::::i \n");
	printf("    SSS::::::::SS    t:::::t          o::::o     o::::oc::::::c     ccccccc k::::::k:::::k      I::::I  N::::::N  N::::N:::::::N i::::i \n");
	printf("       SSSSSS::::S   t:::::t          o::::o     o::::oc:::::c              k:::::::::::k       I::::I  N::::::N   N:::::::::::N i::::i \n");
	printf("            S:::::S  t:::::t          o::::o     o::::oc:::::c              k:::::::::::k       I::::I  N::::::N    N::::::::::N i::::i \n");
	printf("            S:::::S  t:::::t    tttttto::::o     o::::oc::::::c     ccccccc k::::::k:::::k      I::::I  N::::::N     N:::::::::N i::::i \n");
	printf("SSSSSSS     S:::::S  t::::::tttt:::::to:::::ooooo:::::oc:::::::cccccc:::::ck::::::k k:::::k   II::::::IIN::::::N      N::::::::Ni::::::i\n");
	printf("S::::::SSSSSS:::::S  tt::::::::::::::to:::::::::::::::o c:::::::::::::::::ck::::::k  k:::::k  I::::::::IN::::::N       N:::::::Ni::::::i\n");
	printf("S:::::::::::::::SS     tt:::::::::::tt oo:::::::::::oo   cc:::::::::::::::ck::::::k   k:::::k I::::::::IN::::::N        N::::::Ni::::::i\n");
	printf(" SSSSSSSSSSSSSSS         ttttttttttt     ooooooooooo       cccccccccccccccckkkkkkkk    kkkkkkkIIIIIIIIIINNNNNNNN         NNNNNNNiiiiiiii");
}
void menu() {
	printf("\n\n_________________________________________________________________________________________________________________________________________\n");
	printf("*****************************************************************************************************************************************\n");
	printf("Welcome to StockINi stock manager\n\n");
	printf("1  .  Add a product.\n");
	printf("2  .  Show a product.\n");
	printf("3  .  Delete a product.\n");
	printf("4  .  Modify product.\n");;
	printf("5  .  Show all products.\n");
	printf("6  .  Credits.\n");
	printf("7  .  Exit.\n");
	printf("_________________________________________________________________________________________________________________________________________\n");
	printf("*****************************************************************************************************************************************\n");
	printf("NOTE : Please do not press keys repeatedly as it can cause malfunctions.\nREASON : the switch case is develloped with the getchar() function , so please , in every command just input only one key .\n\n");
	printf("Please choose a corresponding key . \n") ;
}
void fullScreen () {
	keybd_event(VK_MENU,0x38,0,0);	
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}
void delay (float number_of_seconds) { 
    float milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock(); 
    while (clock() < start_time + milli_seconds); 
} 
void load() {
	printf("Loading");
	delay(ps);
	printf(".");
	delay(ps);
	printf(".");
	delay(ps);
	printf(".\n");
	delay(ps);
	system("cls");
}
void loadCredits() {
	delay(0.25);
	printf(".");
	delay(0.25);
	printf(".");
	delay(0.25);
	printf(".");
	delay(0.25);
}
void CreditsMenu() {
	system("cls");
	stockINi();
	printf("\n\n\nVersion: %s\n", VERSION);
	puts("GitHub link: {link}\n");
	int i;
	char string[] = "This is an educational project written by: \n";
	for (i = 0; i < strlen(string); i++) {
		putchar(string[i]);
		delay(0.055);
	}
	puts(" Ahmed Malek Tlili");
	delay(0.259);
	puts(" Mohamed Ali Hentati");
	delay(0.259);
	puts(" Mahdi Barhoumi\n");
	printf("Press any key to continue...");
	getch();
}
void InitializeProductsFile() {
	file* ProductsFile = fopen("products.bin", "rb");
	if (ProductsFile == NULL) {
		ProductsFile = fopen("products.bin", "wb");
		unsigned int ProductsNumber = 0;
		fwrite(&ProductsNumber, sizeof(unsigned int), 1, ProductsFile);
	}
	fclose(ProductsFile);	
}
unsigned int GetProductsNumber() {
	file* ProductsFile = fopen("products.bin", "rb");
	unsigned int ProductsNumber;
	fread(&ProductsNumber, sizeof(unsigned int), 1, ProductsFile);
	fclose(ProductsFile);
	return ProductsNumber;
}
int AddProduct(product Product) {
	file* ProductsFile = fopen("products.bin", "rb+");
	unsigned int ProductsNumber, ProductIDBuffer;
	fread(&ProductsNumber, sizeof(unsigned int), 1, ProductsFile);
	int i;
	for (i = 0; i < ProductsNumber; i++) {
		fread(&ProductIDBuffer, sizeof(unsigned int), 1, ProductsFile);
		fseek(ProductsFile, sizeof(product)-sizeof(unsigned int), SEEK_CUR);
		if (Product.id == ProductIDBuffer) {
			fclose(ProductsFile);
			return 0;
		}
	}
	fseek(ProductsFile, sizeof(unsigned int)+sizeof(product)*ProductsNumber, SEEK_SET);
	fwrite(&Product.id, sizeof(unsigned int), 1, ProductsFile);
	fwrite(&Product.quantity, sizeof(unsigned int), 1, ProductsFile);
	fwrite(&Product.name, 100*sizeof(char), 1, ProductsFile);
	fwrite(&Product.brand, 20*sizeof(char), 1, ProductsFile);
	fwrite(&Product.price, sizeof(float), 1, ProductsFile);
	ProductsNumber++;
	fseek(ProductsFile, 0, SEEK_SET);
	fwrite(&ProductsNumber, sizeof(unsigned int), 1, ProductsFile);
	fclose(ProductsFile);
	return 1;
}
int ModifyProduct(unsigned int ProductID, unsigned int ProductNewQuantity, char* ProductNewName, char* ProductNewBrand, float ProductNewPrice) {
	file* ProductsFile = fopen("products.bin", "rb+");
	unsigned int ProductsNumber, IDBuffer;
	fread(&ProductsNumber, sizeof(unsigned int), 1, ProductsFile);
	int i;
	for (i = 0; i < ProductsNumber; i++) {
		fread(&IDBuffer, sizeof(unsigned int), 1, ProductsFile);
		if (ProductID == IDBuffer) {
			fseek(ProductsFile, 0, SEEK_CUR);
			fwrite(&ProductNewQuantity, sizeof(unsigned int), 1, ProductsFile);
			fwrite(ProductNewName, 100*sizeof(char), 1, ProductsFile);
			fwrite(ProductNewBrand, 20*sizeof(char), 1, ProductsFile);
			fwrite(&ProductNewPrice, sizeof(float), 1, ProductsFile);
			fclose(ProductsFile);
			return 1;
		}
		fseek(ProductsFile, sizeof(product)-sizeof(unsigned int), SEEK_CUR);
	}
	fclose(ProductsFile);
	return 0;
}
int RemoveProduct(unsigned int ProductID) {
	file* ProductsFile = fopen("products.bin", "rb+");
	unsigned int ProductsNumber, IDBuffer;
	fread(&ProductsNumber, sizeof(unsigned int), 1, ProductsFile);
	int i;
	for (i = 0; i < ProductsNumber; i++) {
		fread(&IDBuffer, sizeof(unsigned int), 1, ProductsFile);
		if (ProductID == IDBuffer) {
			product ProductBuffer;
			fseek(ProductsFile, sizeof(unsigned int)+sizeof(product)*(--ProductsNumber), SEEK_SET);
			fread(&ProductBuffer.id, sizeof(unsigned int), 1, ProductsFile);
			fread(&ProductBuffer.quantity, sizeof(unsigned int), 1, ProductsFile);
			fread(&ProductBuffer.name, 100*sizeof(char), 1, ProductsFile);
			fread(&ProductBuffer.brand, 20*sizeof(char), 1, ProductsFile);
			fread(&ProductBuffer.price, sizeof(float), 1, ProductsFile);
			fseek(ProductsFile, sizeof(unsigned int)+i*sizeof(product), SEEK_SET);
			fwrite(&ProductBuffer.id, sizeof(unsigned int), 1, ProductsFile);
			fwrite(&ProductBuffer.quantity, sizeof(unsigned int), 1, ProductsFile);
			fwrite(&ProductBuffer.name, 100*sizeof(char), 1, ProductsFile);
			fwrite(&ProductBuffer.brand, 20*sizeof(char), 1, ProductsFile);
			fwrite(&ProductBuffer.price, sizeof(float), 1, ProductsFile);
			fseek(ProductsFile, 0, SEEK_SET);
			fwrite(&ProductsNumber, sizeof(unsigned int), 1, ProductsFile);
			fclose(ProductsFile);
			return 1;
		}
		fseek(ProductsFile, sizeof(product)-sizeof(unsigned int), SEEK_CUR);
	}
	fclose(ProductsFile);
	return 0;
}
product* GetProducts(unsigned int* ProductsNumber) {
	file* ProductsFile = fopen("products.bin", "rb");
	fread(ProductsNumber, sizeof(unsigned int), 1, ProductsFile);
	product* Products = malloc(*ProductsNumber*sizeof(product));
	int i;
	for (i = 0; i < *ProductsNumber; i++) {
		fread(&Products[i].id, sizeof(unsigned int), 1, ProductsFile);
		fread(&Products[i].quantity, sizeof(unsigned int), 1, ProductsFile);
		fread(&Products[i].name, 100*sizeof(char), 1, ProductsFile);
		fread(&Products[i].brand, 20*sizeof(char), 1, ProductsFile);
		fread(&Products[i].price, sizeof(float), 1, ProductsFile);
	}
	fclose(ProductsFile);
	return Products;
}
unsigned int IdLocation( unsigned int x , product* T ) {
	unsigned int i=0, n =GetProductsNumber() ;
	while ( i<n && (T+i)->id !=x ) i++;
	if ( i<= n-1 ) return i;
	else return -1 ;
	
}
    
int main(int argc, char *argv[]) {
	fullScreen();
	InitializeProductsFile();
	while (1) {
		stockINi();
		menu();
		switch(getch()) {
			case '1':
				load();
				system("cls");
				product NewProduct;
				printf("Enter product ID: ");
				scanf("%u", &NewProduct.id);
				fflush(stdin);
				printf("Enter product quantity: ");
				scanf("%u", &NewProduct.quantity);
				fflush(stdin);
				printf("Enter product name: ");
				scanf("%[^\n]s", &NewProduct.name);
				fflush(stdin);
				printf("Enter product brand: ");
				scanf("%[^\n]s", &NewProduct.brand);
				fflush(stdin);
				printf("Enter product price: ");
				scanf("%f", &NewProduct.price);
				fflush(stdin);
				if (AddProduct(NewProduct)) {
					puts("Product added.");
					sleep(3);
				}
				else {
					puts("Product ID match, Please choose a new product ID.");
					sleep(3);
				}
			break;
			case '2':
				load();
				system("cls");
				int i;
				unsigned int ProductsNumber;
				product* Products = GetProducts(&ProductsNumber);
				unsigned int x;
				printf("Enter product ID to show: ");
				scanf("%u", &x);
				fflush(stdin);
				unsigned int y = IdLocation(x, Products);
				if (y == -1) printf("Product not found.\n");
				else {
					printf("ID: %u -- Brand : %s  -- Name : %s -- Quantity: %u -- Price: %.2f$ \n", Products[y].id, Products[y].brand, Products[y].name, Products[y].quantity, Products[y].price);
				}
				free(Products);
				puts("Press any key to continue...");
				getch();
			break;
			case '3':
				load();
				system("cls");
				unsigned int z ;
				printf("Enter a product ID to delete: ");
				scanf("%u",&z);
				fflush(stdin);
				if (RemoveProduct(z)) {
					printf("Product deleted.\n");
					sleep(3);
				}
				else {
					printf("Product not found.\n");
					sleep(3);
				}
			break;
			case '4':
				load();
				system("cls");
				unsigned int ID;
				printf("Enter a product ID to modify: ");
				scanf("%u", &ID);
				fflush(stdin);
				Products = GetProducts(&ProductsNumber);
				unsigned int pos = IdLocation(ID, Products);
				if (pos == -1) {
					puts("Product not found.");
					sleep(3);
				}
				else {
					float price;
					char name[100];
					unsigned int quantity;
					char brand[20];			
					puts("Choose a corresponding key:");
					puts("1. Modify name.\n2. Modify brand.\n3. Modify quantity.\n4. Modify price.");
					switch (getch()) {
						case '1':
							printf("Enter product name: ");
							scanf("%[^\n]s", &name);
							fflush(stdin);
							ModifyProduct(ID, Products[pos].quantity, name, Products[pos].brand, Products[pos].price);
							puts("Product modified.");
							sleep(3);
						break;
						case '2':
							printf("Enter product brand: ");
							scanf("%[^\n]s", &brand);
							fflush(stdin);
							ModifyProduct(ID, Products[pos].quantity, Products[pos].name, brand, Products[pos].price);
							puts("Product modified.");
							sleep(3);
						break;
						case '3':
							printf("Enter product quantity: ");
							scanf("%u", &quantity);
							fflush(stdin);
							ModifyProduct(ID, quantity, Products[pos].name, Products[pos].brand, Products[pos].price);
							puts("Product modified.");
							sleep(3);
						break;
						case '4':
							printf("Enter product price: ");
							scanf("%f", &price);
							fflush(stdin);
							ModifyProduct(ID,  Products[pos].quantity, Products[pos].name, Products[pos].brand, price);
							puts("Product modified.");
							sleep(3);
						break;
					}
				}
			break;
			case '5':
				load();
				system("cls");
				ProductsNumber;
				Products = GetProducts(&ProductsNumber);
				for (i = 0; i < ProductsNumber; i++) {
					printf("ID: %u -- brand : %s  -- Name : %s -- Quantity: %u -- Price: %.2f$\n", Products[i].id, Products[i].brand, Products[i].name, Products[i].quantity, Products[i].price);
				}
				free(Products);
				puts("Press any key to continue...");
				getch();
			break;
			case '6':
				load();
				CreditsMenu();
			break;
			case '7':
				exit(0);
			break ;
			default:
				printf("Invalid option.");
				sleep(1);
			break;
		}
		system("cls");
	}
	return 0;
}

