/* Programma pou parousiazei tropopoiei ta pixels mias eikonas symfona me tin epilogh toy xrhsth*/
#include "hw3a.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
 
/*h synartisi ayth katharizei to buffer , thn xrhsimopoiw kathws merikes printf ektelountai 2 fores*/
void clean_stdin(void){
	int c;    
	do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void rotation(pixelT image[][IMG_SIZE], int *width, int *height){
	int i,j,swap;
	
	pixelT original[IMG_SIZE][IMG_SIZE];
	
	/*krataw ena antigrafo toy pinaka*/
	for(i=0;i<(*height);i++){
		for(j=0;j<(*width);j++){
			original[i][j] = image[i][j];
		}
	}
	/*edw ginetai h antistrofh toy pinaka, parathrw oti oi sthles tou kanonikou ginontai anapodes seires sto antistrofo enw oi sthles toy antistrofou proerxonatai apo thn sxesh height - 1 -i opoy to i ayksanetai se kathe epanalispi, dhladh ksekina apo to telos pros thn arxh*/
	for(i=0;i<(*height);i++){
		for(j=0;j<(*width);j++){
			image[j][(*height - 1) - i] = original[i][j];
		}
	}
	/*to platos tou antistrofou isoutai me to ypsos toy arxikou, enw to to ypsos toy antistrofou isoutai me to platos toy arxikou*/
	swap = (*height);
	(*height) = (*width);
	(*width) = swap;
}

int duplicate(pixelT image[][IMG_SIZE], int *p_width, int *p_height){
	int i,j;
	
	/*elexo an mporw na kanw duplicate ton pinaka,elexontas tin akraia periptwsh*/
	if(((2*(*p_width -1) + 1) > IMG_SIZE) || ((2*(*p_height - 1) + 1) > IMG_SIZE)){
		return(0);
	}
	else{
		for(i=((*p_height) - 1);i>=0;i--){
			for(j=((*p_width) - 1);j>=0;j--){
				image[2*i][2*j] = image[i][j];
				image[2*i + 1][2*j] = image[i][j];
				image[2*i][2*j + 1] = image[i][j];
				image[2*i + 1][2*j + 1] = image[i][j];
			}
		}
		/*allazw to platos kai to ypsos*/
		*p_width = (2*((*p_width)));
		*p_height = (2*((*p_height) ));
		return(1);
	}
}

void gray(pixelT image [][IMG_SIZE], int width, int height){
	int i,j,gray;
	
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			gray = ((image[i][j].red * 0.3) + (image[i][j].green * 0.59) + (image[i][j].blue * 0.11));
			image[i][j].red = gray;
			image[i][j].green = gray;
			image[i][j].blue = gray;
		}
	}
} 

void luminocity(pixelT image[][IMG_SIZE], int width, int height, int max_color, double lum){
	int i, j,red=0, green=0, blue=0;
	
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			red = (image[i][j].red * lum);
			if(red > max_color){
				image[i][j].red = max_color;
			}
			else {
				image[i][j].red = (image[i][j].red * lum);
			}
			
			green = (image[i][j].green * lum);
			if(green > max_color){
				image[i][j].green = max_color;
			}
			else {
				image[i][j].green = (image[i][j].green * lum);
			}
			
			blue = (image[i][j].blue * lum);
			if(blue > max_color){
				image[i][j].blue = max_color;
			}
			else {
				image[i][j].blue = (image[i][j].blue * lum);
			}
		}
	}
}

void option(void){
	printf("\nEnter option:\n");
	printf("	Print image to screen: (P/p)\n");
	printf("	Load another image: (L/l)\n");
	printf("	Save image: (S/s)\n");
	printf("	Change luminocity: (U/u)\n");
	printf("	Convert to grayscale: (G/g)\n");
	printf("	Duplicate size: (D/d)\n");
	printf("	Rotation: (R/r)\n");
	printf("	Quit: (Q/q)\n");
}

void print(int width_pic, int height_pic, int max_color_pic,pixelT image[][IMG_SIZE]){
	int i=0,j=0;
	
	printf("\n========== IMAGE ==========\n");
	printf("%d %d %d\n",width_pic,height_pic,max_color_pic);
	for(i=0;i<height_pic;i++){
		for(j=0;j<width_pic;j++){
			printf("%d",image[i][j].red);
			printf(" ");
			printf("%d",image[i][j].green);
			printf(" ");
			printf("%d",image[i][j].blue);
			if(j!=width_pic - 1 ){
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("===========================\n\n");
	printf("\n#\n");	
}

int main (int argc, char *argv[]) {
	
    pixelT pinax_pic[IMG_SIZE][IMG_SIZE];
    int width_pixels, height_pixels, max_color,i,j;
    char file_path[PATH_SIZE],true_file_path[PATH_SIZE],new_path[PATH_SIZE];
    int true_size,return_load,return_save,dup;
	char user_option;
	double lum;
    
	
	true_size = PATH_SIZE + 2; /*to kanoume auto gia na mporoume na diavasoume mexri kai 255 xarakthres*/
	
	while(1){
		printf("\nEnter image path: ");
		fgets(file_path , true_size , stdin);

		/*vriskw to \n poy diavazei h fgets kai to antikathistw me \0*/
		i=0;
		while(file_path[i] != '\n'){
			true_file_path[i] = file_path[i];
			i++;
		}
		true_file_path[i] = '\0';
		/*arxikopoiw ton pinaka me ' '*/
		for(i=0;i<IMG_SIZE;i++){
			for(j=0;j<IMG_SIZE;j++){
				pinax_pic[i][j].red = ' ';
				pinax_pic[i][j].green = ' ';
				pinax_pic[i][j].blue = ' ';
			}
		}
		/*edw elengei an to path tou xrhsth einai sxetiko h apolito*/
		if(true_file_path[0] != '/' && true_file_path[1] != 'h' && true_file_path[2] != 'o' && true_file_path[3] != 'm' && true_file_path[4] != 'e'){
			strcpy(new_path, "/home/prog1/");
			strcat(new_path, true_file_path);
		}
		else{
			strcpy(new_path, true_file_path);
		}

		return_load = load_image(new_path, pinax_pic, &width_pixels, &height_pixels, &max_color);
		
		if(return_load == 0){
			printf("\nInvalid path!\n");
			continue;
		}
		if(return_load == 1){
			printf("\nLoad OK!\n");
			printf("\n#\n");
			break;
		}
	}
	/*elegxei thn epilogh tou xrhsth kai trexei thn analogh sinartish*/
	while(1){ 
		option();
		scanf("%c", &user_option);
		switch (user_option) {
			case('P'):
			case('p'):{
				print(width_pixels, height_pixels, max_color, pinax_pic);
				clean_stdin();
				break;
			}
			case('L'):
			case('l'):{
				while(1){
					printf("\nEnter image path: ");
					clean_stdin();
					fgets(file_path , true_size , stdin);
					i=0;
					while(file_path[i] != '\n'){
						true_file_path[i] = file_path[i];
						i++;
					}
					true_file_path[i] = '\0';
					
					for(i=0;i<IMG_SIZE;i++){
						for(j=0;j<IMG_SIZE;j++){
							pinax_pic[i][j].red = ' ';
							pinax_pic[i][j].green = ' ';
							pinax_pic[i][j].blue = ' ';
						}
					}
					
					if(true_file_path[0] != '/' && true_file_path[1] != 'h' && true_file_path[2] != 'o' && true_file_path[3] != 'm' && true_file_path[4] != 'e'){
						strcpy(new_path, "/home/prog1/");
						strcat(new_path, true_file_path);
					}
					else{
						strcpy(new_path, true_file_path);
					}
					return_load = load_image(new_path, pinax_pic, &width_pixels, &height_pixels, &max_color);
					if(return_load == 0){
						printf("\nInvalid path!\n");
						continue;
					}
					if(return_load == 1){
						printf("\nLoad OK!\n");
						printf("\n#\n");
						break;
					}
				}
				break;
			}
			case('S'):
			case('s'):{
				while(1){
					printf("\nEnter new image path: ");
					clean_stdin();
					fgets(file_path , true_size , stdin);
					
					i=0;
					while(file_path[i] != '\n'){
						true_file_path[i] = file_path[i];
						i++;
					}
					true_file_path[i] = '\0';
					if(true_file_path[0] != '/' && true_file_path[1] != 'h' && true_file_path[2] != 'o' && true_file_path[3] != 'm' && true_file_path[4] != 'e'){
						strcpy(new_path, "/home/prog1/");
						strcat(new_path, true_file_path);
					}
					else{
						strcpy(new_path, true_file_path);
					}
					return_save = save_image(new_path, pinax_pic, width_pixels, height_pixels, max_color);
					if(return_save == 0){
						printf("\nInvalid path!\n");
						continue;
					}
					if(return_save == 1){
						printf("\nSave OK\n");
						printf("\n#\n");
						break;
					}
				}
				break;
			}
			case('U'):
			case('u'):{
				while(1){
					printf("\nEnter luminocity factor: ");
					scanf("%lf" , &lum);
					if(lum <= 0 || lum > 2){
						printf("\nFactor should be between (0,2]\n");
						continue;
					}
					else{
						luminocity(pinax_pic, width_pixels, height_pixels, max_color, lum);
						printf("\nLuminocity OK!");
						printf("\n#\n");
						clean_stdin();
						break;
					}
				}
				break;
			}
			case('G'):
			case('g'):{
				gray(pinax_pic, width_pixels, height_pixels);
				printf("\nGrayscale OK!");
				printf("\n#\n");
				clean_stdin();
				break;
			}
				
			case('D'):
			case('d'):{
				dup = duplicate(pinax_pic, &width_pixels, &height_pixels);
				if(dup == 0){
					printf("\nDuplication NOT OK!");
				}
				if(dup == 1){
					printf("\nDuplication OK!");
				}
				printf("\n#\n");
				clean_stdin();
				break;
			}
			case('R'):
			case('r'):{
				rotation(pinax_pic, &width_pixels, &height_pixels);
				printf("\nRotation OK!");
				printf("\n#\n");
				clean_stdin();
				break;
			}
			case('Q'):
			case('q'):{
				return 0;
			}
			default:{
				option();
				break;
			}
		}
	}
	return 0;
}
