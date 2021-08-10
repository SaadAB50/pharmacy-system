#include <stdio.h>
#include <string.h>
#include<windows.h>

#define NAME_LEN 20
#define PW_LEN 20

//--------sales info-------
struct salesinfo{
	float sale;
	int date[3];
	char medicine[20];
	int quantity;
	float scost;
};


//--------stores uname and password-------
struct user{
	char name[NAME_LEN+1];
	char password[PW_LEN+1];

};

//-------medicine info--------
struct medicine{
	char mname[NAME_LEN+1];
	int qty;
	float price; 
	float cost;          
};

//------order details-----
struct order{
	char address[NAME_LEN+20];
	char number[NAME_LEN];
	char oname[NAME_LEN+1];
	int oqty;
	char omed[NAME_LEN+1];
	float total;
};

//----Main functions---
void signUp();
void signIn();


//---Portals----
void manager();
void admin();
void customer();

//--------MANAGER FUNCTIONS + ADMIN FUNCTIONS-------
void orders();
void viewstocks();
void addstocks();
void feedbacks();
void viewstockscustomer();
void vouchers();
void managerrequests(); 
void salesadmin();
void salesmanager();
void deleteusers();


//main menu
int main(void){
	
	//Date
	SYSTEMTIME stime;
	GetSystemTime(&stime);
	printf("\n\n\nDate: %d / %d / %d\n",stime.wDay,stime.wMonth,stime.wYear);



printf("\n\n\t\t\t\t\t\t___SAA MEDICAL STORE___\n\n");                            
printf("\n\t\t\t\t\t\t1. SignIn\n\n\t\t\t\t\t\t2. SignUp\n\n\n\n\t\t\t\t\tpress 1 or 2 to continue: ");           
int choice;
scanf("%d",&choice);
getchar();
if(choice==1)
{
	signIn();
}
else if(choice == 2)
{
	signUp();
}
else
{
	printf("\n\n\t\t\t\t\t\twrong choice");
	main();
}

	return 1;
}


//SIGN UP
void signUp(){
    //CUSTOMER
	struct user u;
	struct user file;
	
	 //get username and password
	printf("\n\n\n\t\t\tEnter username: ");
	gets(u.name);
	printf("\t\t\tEnter password: ");
	gets(u.password);
	
	 // validation for unique username 
	FILE * fp = fopen("logininfo.bin", "ab+");
	
	for(;;)
	{
		fread(&file,sizeof(struct user),1,fp);
		
		if(feof(fp)!=0){
		break;
	}
		
		else
		{
			if(strcmp(u.name,file.name)==0)
			{
				printf("\n\t\t\tUser name already exists, choose a unique username\n");
				signUp();
			}
		}
	}
	
	fclose(fp);
	//store in file
		fp = fopen("logininfo.bin", "ab");
		fwrite(&u,sizeof(struct user),1,fp);
		fclose(fp);
		printf("\n\t\t\tSign Up successful!\n You can now login\n");
		main();
}




//SIGN IN
void signIn(){                                                                             
	struct user user;
	struct user fileUser;
	
	
    //get username and password from user
	printf("\n\n\n\t\t\tEnter username: ");
	gets(user.name);
	printf("\t\t\tEnter password: ");
	gets(user.password);

    //ADMIN AND MANAGER's id password are hardcoded
	if(strcmp(user.name, "Anas") == 0 && strcmp(user.password, "m1234") == 0)                
		{
			printf("\n\n\t\t\t\t\t\t___Welcome Manager___\n");
			manager();
		}
	else if(strcmp(user.name, "Saad") == 0 && strcmp(user.password, "a1234") == 0)
		{
			printf("\n\n\t\t\t\t\t\t___Welcome Admin___");
			admin();
		}
	else
	{
	//regular customers
	FILE * fp = fopen("logininfo.bin", "ab+");
	
	
    //search user in file
	for ( ; ; ){
		fread(&fileUser, sizeof(struct user), 1, fp);
		//base case to end loop
        if (feof(fp) != 0){
				break;
		}

        //comparison with file data
		if (strcmp(user.name, fileUser.name) == 0 && strcmp(user.password, fileUser.password) == 0){
			printf("\n\n\t\t\t\t\t\t_Welcome %s_\n", user.name);
			customer();
		}
	}
	printf("\n\n\n\t\tUser doesnt exist. Create a new account to continue");
		    main();
}
}

void manager(){
	FILE *fp;
	char requests[100];
	
	printf("\n\n\n\t\t\t\t1. View Pending orders\n\t\t\t\t2. View Stocks\n\t\t\t\t3. Request Admin\n\t\t\t\t4. Add/View vouchers\n\t\t\t\t5. Logout\n\t\t\t\t6. Generate sales report\n\n\n\n\t\t\t\tEnter your choice: ");
	char choice;
	scanf(" %c",&choice);
	getchar();
	switch(choice)
	{
		case '1':
			orders();     //Manager can view orders and confirm pending orders
			break;
			
		case '2':
			viewstocks(); //Manager can view stocks and add medicines and quantity
			manager();
			break;
		
	    case '3':	      //Manager can request admin for anything
		    fp = fopen("requests.bin","ab");
	     	printf("\n\n\t\t\t\tEnter your request: ");
	    	fflush(stdin);
		    gets(requests);
	    	fflush(stdin);
	    	fwrite(&requests, sizeof(requests),1,fp);
	    	fclose(fp);
	     	printf("\n\t\t\t\tYour request has been sent to admin\n");
	    	manager();
	    	break;	
		
     	case '5':      //logout to main
			main();
			break;	
			
		case '4':       //manager can add vouchers
	    	vouchers();
	    	break;	
		
		case '6':
		printf("\n\n\n");          //generate sales report
			salesmanager();
			break;
		
		default:                    
			printf("\n\t\t\t\tWrong choice");
			manager;
				
	}
	
	
}



void admin(){
	printf("\n\n\n\t\t\t\t1. View feedbacks\n\t\t\t\t2. View profit and sales info\n\t\t\t\t3. Add stocks\n\t\t\t\t4. View Manager's requests\n\t\t\t\t5. Sign out\n\t\t\t\t6. View Stocks\n\t\t\t\t7. Delete users\n\t\t\t\t8. Access Manager controls\n\t\t\t\t\n");
	char choice;
	scanf(" %c",&choice);
	getchar();
	switch(choice)
	{
		case '1':
			feedbacks();     
			break;
			
		case '2':
	     	salesadmin();
			break;
		
		case '3':
			addstocks();
			break;
		
		case '4':
			managerrequests(); 
			break;	
		
		case '5':
			main();
			break;	
			
		case '6':
		    viewstocks();
		    admin();
		    break;
		
		case '7':
		    deleteusers();
		    admin();	
		    break;
		
		case '8':
		    manager();	
		    break;
		
	
				
		
		default:
			printf("\nWrong choice");
			admin;
	}
	
	
}


void customer(){
	char medi[21];
	int quant;
	struct medicine m; int i;
	int x;      //structure to read from user to compare with file's data
	struct medicine mfile;         //structure to read from file and compare with user's data
	struct order o;      
	struct medicine marray[30];    // structure to read order details from user and write in file
	char mname[NAME_LEN];
	char userinput[21];            // stores medicine name input by user for further usage
	int qty;
	char feedback[100];
	int flag = 0;
	struct medicine count;
	struct salesinfo sinfo;

	//Customer page
	printf("\n\n\n\t\t\t\t1. Order now\n\t\t\t\t2. Post feedback\n\t\t\t\t3. SignOut\n\t\t\t\t4. View Medicines\n");
	printf("\n\t\t\tpress 1, 2, 3 or 4 ");
	scanf("%d",&x);
	getchar();
	
	if(x==1){
		
	printf("\nType the medicine name and quantity\n");
	gets(m.mname);
	fflush(stdin);
	strcpy(userinput,m.mname); //value stored for further usage
	fflush(stdin);
	scanf("%d",&m.qty);
	fflush(stdin);
	int userqty = m.qty; //value stored for further usage
	
	//searches for medicine name and required qty from file
	FILE *fp = fopen("medicineinfo.bin", "ab+");
	
	int i;
	for(;;){                                                                  
		fread(&mfile, sizeof(struct medicine), 1, fp);
		
		if (feof(fp)){
			
				break;
		}
		else if (strcmp(m.mname, mfile.mname) == 0 && mfile.qty>=m.qty){
			
			printf("\n\n\t\t\t\t\t_MEDICINE AVAILABLE_\n\n\n");
			//stores medicine name and quanity for SALES RECORD	
			strcpy(sinfo.medicine, m.mname);
			sinfo.quantity = m.qty;
			sinfo.scost = m.qty * mfile.cost;
			
			
			//flag set to 1 if medicine exists
			    flag = 1;
				fclose(fp);
				fp = fopen("orders.bin", "ab");
				
				
				
				
				//take more details to confirm order
				strcpy(o.omed,m.mname);
				o.oqty = m.qty;
				printf("\n\n\n\t\t\tProvide details for processing your order\n\nEnter your address: ");
				fflush(stdin);
				gets(o.address);
				fflush(stdin);
				printf("Enter your name: ");
				fflush(stdin);
				gets(o.oname);
				printf("Enter Phone number: ");
				fflush(stdin);
				gets(o.number);
				fflush(stdin);
				printf("Enter voucher code for 10 percent discount (5 characters long), press any key to skip: ");
				fflush(stdin);
				char voucher[6];
				fflush(stdin);
				scanf("%s",&voucher);
				fflush(stdin);
				
				
				
				//calculate total considering voucher or not
				FILE *fptr;
				char filevoucher[6];                    
				int flag1 = 0;
				fptr = fopen("vouchers.bin","ab+");
				while(!feof(fptr))
				{
					fread(&filevoucher,sizeof(voucher),1,fptr);
					if(strcmp(filevoucher,voucher)==0)
					{
						
						//flag if voucher found in file
						flag1 = 1;                     
						printf("\n\n\n\t\t\tCongratulations! You got a 10 percent discount of RS %f\n",((0.1)*(userqty * mfile.price)));
						o.total = (userqty * mfile.price)-((0.1)*(userqty * mfile.price));
						break;
					}
				}
				
				
				//flag is 0, means no voucher is applied and calculate total normally
				if(flag1==0)                                
				{
					    printf("\n\n\t\t\tVoucher not applied!\n");
						o.total = userqty * mfile.price; 
				}
				fclose(fptr);
				
				
				
				//stores TIME AND TOTAL FOR SALES RECORD AND PUT IN FILE
				SYSTEMTIME stime;
	            GetSystemTime(&stime);
	            
	            
	
				sinfo.sale = o.total;
				sinfo.date[0] = stime.wDay;
				sinfo.date[1] = stime.wMonth;
				sinfo.date[2] = stime.wYear;
				
				
				
				FILE *fp2 = fopen("sales.bin","ab+");	
				fwrite(&sinfo,sizeof(struct salesinfo),1,fp2);
				fclose(fp2);
				
				
				
				
				
				//write order details in file
				fwrite(&o, sizeof(struct order), 1, fp);
				fclose(fp);
				
				

                //writing file contents to array and change the quantity, since user has bought stuff
				fp = fopen("medicineinfo.bin", "rb");
				
				int linecount=0;
				
				//count structures in file
				while(!feof(fp))
				{
					fread(&count,sizeof(struct medicine),1,fp);
					linecount++;
				}
				fclose(fp);
				
				
				fp = fopen("medicineinfo.bin", "ab+");
				for(i=0;i<linecount-1;i++){                                          
		            fread(&mfile, sizeof(struct medicine), 1, fp);
		            if (feof(fp)){
			            break;
	                }
					strcpy(marray[i].mname, mfile.mname);
					marray[i].price = mfile.price;
					marray[i].cost = mfile.cost;
			
					if(strcmp(marray[i].mname,userinput)==0)          //if medicine found in array
					{
						marray[i].qty = mfile.qty - userqty;         // quantity in stock is reduced and copied to array structure
					}
					else{
						marray[i].qty = mfile.qty;
					}
				}
				fclose(fp);         
				
				
                //overwrite  array into FILE   // write new medicine info to file
                fp = fopen("medicineinfo.bin","wb");                        
				for(i=0;i<linecount-1;i++){
		            if (feof(fp)){
				        break;
		            }
			        
					    fwrite(&marray[i], sizeof(struct medicine), 1, fp);    
		        }
		        fclose(fp);
		        printf("\n\t\t\t\t__Your order has been placed___\n\t\t\t\tTotal Amount: Rs %f\n",o.total);
		        
		        customer();
	        
        }
        
		else{continue;}
		
		
	//flag remains 0, since medicine doesnot exist or the stock is empty	
    }
    if(flag==0){
    	printf("\nMedicine does not exist or the stock is empty\n");
    	customer();
	}
    fclose(fp);
}
else if(x==2)
{
	FILE *fb;
	printf("\nWrite your feedback here: ");
	fflush(stdin);
	gets(feedback);
	fb = fopen("feedback.bin","ab");
	fwrite(feedback,sizeof(feedback),1,fb);
	fclose(fb);
	printf("\nFeedback sent!\n");
	customer();
}
else if(x==3)
{
	main();
}
else if(x==4)
{
	viewstockscustomer();
	customer();
}
}

void orders(){
	
	struct order orderfile;                            // to copy order details from file to struct
	printf("\n\n\n\t\t\t\t\t___ORDERS___");
	FILE * fp = fopen("orders.bin", "ab+");	
                                                       //read order info from file and display to manager
	for ( ; ; ){
		fread(&orderfile, sizeof(struct order), 1, fp);
		//base case to end loop
        if (feof(fp) != 0){
				break;
		}
		printf("\n\n\nName: %s\nAddress: %s\nPhone Number: %s\nQty: %d\nMedicine: %s\nTotal: %f",orderfile.oname,orderfile.address, orderfile.number,orderfile.oqty,orderfile.omed,orderfile.total);
	}
	printf("\n\n\n\t\t\t\t1. Home\n\t\t\t\t2. Confirm all orders\n");
	int choice;
	scanf("%d",&choice);
	getchar();
	if(choice==1){
		fclose(fp);
	manager();
}
	else if(choice==2){
	fclose(fopen("orders.bin", "w"));	
	printf("\n\t\t\t___All orders are confirmed!___");
	manager();	
}

}


//manager can add stocks
void addstocks(){
	struct medicine mfile;
FILE *fp;
printf("\nEnter Medicine Name: ");
fflush(stdin);
gets(mfile.mname);
fflush(stdin);
printf("\nEnter Sale Price: ");
scanf("%f",&mfile.price);
fflush(stdin);
printf("\nEnter Cost Price: ");
fflush(stdin);
scanf("%f",&mfile.cost);
fflush(stdin);
printf("\nEnter quantity: ");
scanf("%d",&mfile.qty);
fflush(stdin);

fp = fopen("medicineinfo.bin","ab");
fwrite(&mfile, sizeof(struct medicine), 1, fp);
fclose(fp);
fflush(stdin);
printf("\n__Stock succesfully added!__\nPress 1 to add more stocks, Press any key to return to admin's page  ");
int x;
scanf("%d",&x);
getchar();
if(x==1)
{
	addstocks();
}
else
{
	admin();
}
}
void viewstocks(){
	struct medicine filemedicine;
	printf("\n\n\t\t\t\t\t_STOCKS_\n");
	FILE * fp = fopen("medicineinfo.bin", "ab+");
    //read medicine info from file and display to manager
	for ( ; ; ){
		fread(&filemedicine, sizeof(struct medicine), 1, fp);
		//base case to end loop
        if (feof(fp) != 0){
				break;
		}
		printf("\n\t\t\tMedicine name: %s\t\t\tSale Price:RS %f\t\t\tCost Price: %f\t\t\tQty: %d\n",filemedicine.mname,filemedicine.price, filemedicine.cost,filemedicine.qty);
	}
	fclose(fp);
		
}



void feedbacks(){
	
	char fback[100];
	int i;
	printf("\n__CUSTOMERS' FEEDBACKS__\n\n");
	FILE *fb;
	fb = fopen("feedback.bin","ab+");
	
	for ( ; ; ){
		if (feof(fb) != 0){
				break;
		}
		fread(&fback, sizeof(fback), 1, fb);
        printf("> %s\n",fback);
        
    }
    fclose(fb);
	admin();	
}


void viewstockscustomer(){
	struct medicine filemedicine;
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t_STOCKS_\n\n\n");
	FILE * fp = fopen("medicineinfo.bin", "ab+");	
    //read medicine info from file and display to manager
	for ( ; ; ){
		fread(&filemedicine, sizeof(struct medicine), 1, fp);
		//base case to end loop
        if (feof(fp) != 0){
				break;
		}
		printf("\n\t\t\tMedicine name: %s\t\t\tSale Price:RS %f\t\t\tQty: %d\n",filemedicine.mname,filemedicine.price, filemedicine.qty);
	}
	fclose(fp);
}

void vouchers(){
	FILE *fp;
	int i=1;
	char voucher[5];
	fp=fopen("vouchers.bin","ab+");
	printf("\n\n\n\n\n\t\t\t\t\t___Current Vouchers___\n\n");
	for(;;){
		fread(&voucher,sizeof(voucher),1,fp);
		if(feof(fp)!=0)
		break;
		
		else{
		printf("\t\t%d) %s\n",i,voucher);
		i++;}
	}
	
	printf("\n\n\n\n\n\n\t\t\tPress 1 to add voucher, 2 to clear all vouchers: ");
	int choice; scanf("%d",&choice);
	
	if(choice==1){
	printf("\n\nEnter voucher(five lettered): ");
	scanf("%s",&voucher);
	fwrite(&voucher,sizeof(voucher),1,fp);
	printf("\n\t\t\tVOUCHER ADDED!\n\n\n\n\n");
	fclose(fp);
	manager();
}
else{
	fp = fopen("vouchers.bin","wb");
	fclose(fp);
	printf("\n\n\t\t\tALL VOUCHERS HAVE BEEN CLEARED!\n\n\n\n\n");
	manager();
}

}

void managerrequests(){
	char requests[100];
	printf("\n\n\t\t\t__MANAGER REQUESTS__\n\n");
	FILE *fp;
	fp = fopen("requests.bin","ab+");
	for(;;)
{
	fread(&requests, sizeof(requests), 1, fp);
	if(feof(fp)!=0)
	break;
	
	else
    printf("> %s\n",requests);
}
        
    
    fclose(fp);
	printf("\n\n\n\n\n\n\t\t\tEnter 1 to go back or 2  if all requests are processed: ");
	int choice;
	scanf("%d",&choice);
	getchar();
	
	if(choice==1)
	admin();
	
	else if(choice==2)
	{
		FILE *fptr;	
		fptr = fopen("requests.bin","wb");
		fclose(fptr);
		printf("\n\n\nAll manager's requests are processed ");
		admin();
	}	

}


void salesmanager(){
	//manager can view sales info with date
	float sales=0;
	struct salesinfo sinfo;
	FILE *fp;
	fp = fopen("sales.bin","ab+");
	int i=1;
	printf("\n\n\n\t\t\t\t\tSALES INFO\n");
	for(;;)
	{
		fread(&sinfo,sizeof(struct salesinfo),1,fp);
		if(feof(fp)!=0)
		break;
		
		else {
		printf("\n\n%d) Medicine: %s\t\tQty: %d\t\tSale: %f\t\tDate:%d/%d/%d\n",i,sinfo.medicine, sinfo.quantity, sinfo.sale, sinfo.date[0],sinfo.date[1],sinfo.date[2]);
		i++;
	}
	
	}
	
	fclose(fp);
	
	
	printf("\n\n\t\t\tPress 1 to go back: ");
	int choice;
	scanf("%d",&choice);
	manager();
}	



void deleteusers(){
	//DISPLAYS USER INFO
	struct user userinfo;
	struct user count;
	int i=1;
	printf("\n\n\n\n__Currently registered users__\n\n");
	FILE *fp = fopen("logininfo.bin","rb");
	for(;;)
	{
		
		fread(&userinfo,sizeof(struct user),1,fp);
		if(feof(fp)!=0)
		break;
		
		else{
		printf("%d. Username: %s\n   Password: %s\n\n",i,userinfo.name,userinfo.password);
		i++;}
	}
	fclose(fp);
	
	
	char n[21];
	printf("\nWhich user you want to delete? Enter username: ");
    gets(n);
	
	
	
	//counts users in file
	FILE *fp1 = fopen("logininfo.bin", "rb");
				    
				int linecount=0;
				while(!feof(fp1))
				{
					fread(&count,sizeof(struct user),1,fp1);
					linecount++;
				}
				fclose(fp1);
	struct user userinfo1;
	struct user userinfoarray[30];
	
	
	
	//copies users into array except deleted one
	FILE *fp2 = fopen("logininfo.bin","rb");
	for(i=0;i<linecount-1;i++)
	{
		fread(&userinfo1,sizeof(struct user),1,fp2);
		
		if(strcmp(userinfo1.name,n)==0){           
			continue;
	}
	
	//copies username to array if username is not matched
	else{                                             
		strcpy(userinfoarray[i].name,userinfo1.name);
		strcpy(userinfoarray[i].password,userinfo1.password);
	}
		
	}
	fclose(fp2);
	
	
	
	
	//rewrite users
	FILE *f;
	f = fopen("logininfo.bin","wb");
	for(i=0;i<linecount-1;i++){
		            if (feof(f)){
				        break;
	}
			        
					    fwrite(&userinfoarray[i], sizeof(struct user), 1, f);    
	}
	fclose(f);
	printf("\n\t\t\t\tUser %s has been removed!",n);
	admin();	        
}


void salesadmin(){
	float sales=0;
	float costs = 0;
	struct salesinfo sinfo;
	FILE *fp;
	fp = fopen("sales.bin","ab+");
	int i=1;
	printf("\n\n\n\t\t\tFOLLOWING ARE THE SALES AND PROFIT INFO\n\n\n")
	for(;;)
	{
		fread(&sinfo,sizeof(struct salesinfo),1,fp);
		if(feof(fp)!=0)
		break;
		
		else {	
		sales = sinfo.sale + sales;
		costs = costs + sinfo.scost;
		printf("\n\t%d) Medicine: %s\t\tQty: %d\t\tSale: %f\t\tDate:%d/%d/%d\n",i,sinfo.medicine, sinfo.quantity, sinfo.sale, sinfo.date[0],sinfo.date[1],sinfo.date[2]);
		i++;
	}
	}
	
	fclose(fp);
	printf("\n\n\n\t\t\t\t__TOTAL SALES: RS %f__\n\n\t\t\t\t__TOTAL PROFIT: RS %f_\n\n\nPress 1 to clear sales and profit info, 2 to go back:  ",sales,sales-costs);
	int choice;
	scanf("%d",&choice);
	if(choice==1){
	fp = fopen("sales.bin","wb");
	fclose(fp);
	printf("\n\n\t\t\tSales info have been cleared");
	admin();
}	
else
admin();
}
