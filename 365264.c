// Numara: 365264 - Ad, soyad: İbrahim Yılmaz - Gmail: ibrahimyilmaz026@gmail.com // TEK YAPTIM.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void takimlar_oku();
void takimlar_yazdir();
void lig_ayarlar_oku();
void lig_ayarlar_yazdir();
void mac_listesi_oku();
void mac_listesi_yazdir();
void lig_durumtablosu_yazdir();
void mac_listesi_girdial();
void takimlar_standart_harf_guncelle();
void takimlar_buyuk_harf_guncelle();
void takimlar_kucuk_harf_guncelle();
void lig_sirala_puan();
void lig_sirala_takmaisim();
void lig_sirala_isim();
void struct_yerdegistir(int a, int b);
void mac_listesi_guncelle(char gecicimaclar[][4]);
int oynanan_mac_test(char takim1, char takim2);
void lig_puan_durumu_dosyaya_yazdir();

struct takim {
	char takmaismi;
	char uzunismi[13];
	int oynananmac;
	int galibiyet;
	int beraberlik;
	int maglubiyet;
	int atilangol;
	int yenilengol;
	int averaj;
	int puan;
};
struct takim *takimlar;

struct mac {
	char birinci_takim_adi;
	int birinci_takim_gol_sayisi;
	char ikinci_takim_adi;
	int ikinci_takim_gol_sayisi;
};
struct mac *maclar;

struct gecicistruct {
	char takmaismi;
	char uzunismi[13];
	int oynananmac;
	int galibiyet;
	int beraberlik;
	int maglubiyet;
	int atilangol;
	int yenilengol;
	int averaj;
	int puan;
} gecicistruct;	//takımları sıralarken swap işlemi için.

int takimsayisi;
int macsayisi = 0;
int ayarlar[4]; //ayarlar[0] = max takım sayısı, ayarlar[1] = galibiyette alınacak puan, ayarlar[2] = Beraberlikte alınacak puan, ayarlar[3] = Mağlubiyette alınacak puan.
char gecici_takmaismi;

void main()
{	
	takimlar = (struct takim*)malloc(26 * sizeof(struct takim));
	char yapilacak_islem;
	char nasil_yazdir;
	char nasil_sirala;
	takimlar_oku();
	takimlar = (struct takim*)realloc(takimlar, takimsayisi * sizeof(struct takim));
	lig_ayarlar_oku();
	maclar = (struct mac*)malloc(100 * sizeof(struct mac));
	mac_listesi_oku();
	maclar = (struct mac*)realloc(maclar, ((--takimsayisi * ++takimsayisi) + 1) * sizeof(struct mac));

	printf("_________________________________________________________________ \n"
		"SPOR TOTO SÜPER LİGİNE HOŞGELDİNİZ \n"
		"_________________________________________________________________ \n"
		"1: Takım listesini yazdır. \n"
		"2: Lig ayarlarını yazdır. \n"
		"3: Lig puan durum tablosunu yazdır. \n"
		"4: Maç skorunu gir. \n"
		"5: Maç Listesini yazdır. \n"
		"6: Lig puan durumunu dosyaya yazdır. \n"
		"0: Uygulamadan çık. \n"
		"_________________________________________________________________ \n");

	while(1){
	printf("\nLütfen yapmak istediğiniz işlemi tuşlayınız: ");
	scanf("%c", &yapilacak_islem);
	getchar();
		switch(yapilacak_islem)
		{
			case '0':
				return;
			case '1':
				printf("0: Baş harfleri büyük yazdır. \n"
					"1: Büyük harf ile yazdır. \n"
					"2: Küçük harf ile yazdır. \n"
					"Nasıl yazdırmak istediğinizi tuşlayınız: ");
				scanf("%c", &nasil_yazdir);
				getchar();
				switch(nasil_yazdir)
				{
					case '0':
						takimlar_standart_harf_guncelle();
						takimlar_yazdir();
						break;
					case '1':
						takimlar_buyuk_harf_guncelle();
						takimlar_yazdir();
						break;
					case '2':
						takimlar_kucuk_harf_guncelle();
						takimlar_yazdir();
						break;
					default:
						printf("HATA! Yanlış tuşlama yaptınız.\n");
						break;
				}
				break;
			case '2':
				lig_ayarlar_yazdir();
				break;
			case '3':
				printf("0: Takma isime göre sırala. \n"
					"1: Puana göre sırala. \n"
					"2: İsme göre sırala. \n"
					"Nasıl sıralamak istediğinizi tuşlayınız: ");
				scanf("%c", &nasil_sirala);
				getchar();
				switch(nasil_sirala)
				{
					case '0':
						lig_sirala_takmaisim();
						lig_durumtablosu_yazdir();
						break;
					case '1':
						lig_sirala_puan();
						lig_durumtablosu_yazdir();
						break;
					case '2':
						lig_sirala_isim();
						lig_durumtablosu_yazdir();
					default:
						printf("HATA! Yanlış tuşlama yaptınız.\n");
						break;
				}
				break;
			case '4':
				mac_listesi_girdial();
				break;
			case '5':
				mac_listesi_yazdir();
				break;
			case '6':
				lig_puan_durumu_dosyaya_yazdir();
			case '\n':
			case '\t':
			case ' ':
				break;
			default:
				printf("Yanlış tuşlama yaptınız! Lütfen tekrar tuşlama yapınız.\n");
				break;
		}
	}
	return;
}

void takimlar_oku()
{
	lig_ayarlar_oku();	//Maksimum girilebilecek takım sayısını çekmek için.
	char ch1;
	gecici_takmaismi = 'A';
	int satir = 0;
	int karakter = 0;
	int son = 0;
	FILE *fp = fopen("takimlar.txt", "r");
	char takimismi[13];
	while(!feof(fp))
	{
		if(satir == ayarlar[0]) { break; } //Maximum takim sayisi kadar yazdirmak icin.
		ch1 = getc(fp);
		if(ch1 == '\n' && (takimismi[0] == ' ' || karakter == 0))
		{
			karakter = 0;
		}
		else if(karakter < 12 && ch1 != '\n')
		{
			takimismi[karakter++] = ch1;
		}
		else if(ch1 == '\n' && takimismi[0] != ' ')
		{
			takimismi[karakter] = '\0';
			for(int i = 0; i < karakter; i++)
			{
				takimlar[satir].uzunismi[i] = takimismi[i];
			}
			takimlar[satir].takmaismi = gecici_takmaismi;
			gecici_takmaismi++;
			karakter = 0;
			satir++;
		}
	}
	takimsayisi = satir;
	fclose(fp);
}

void takimlar_yazdir() 	//Takımları yazdırır.
{
	printf("Ligteki takımlar listesi şu şekildedir: \n");
	for(int i=0; i < takimsayisi; i++)
	{
		printf("%s\n", takimlar[i].uzunismi);
	}
}

void lig_ayarlar_oku()	//Lig ayarlarını okur.
{
	char ch2;
	int satir = 0;
	int son = 0;
	int karakter = 0;
	FILE *fp2 = fopen("ayarlar.txt","r");
	char geciciayarlar[5];
	while(!feof(fp2))
	{
		ch2 = getc(fp2);
		if(ch2 != '(' && ch2 != '\n' && satir == son)
		{
			geciciayarlar[karakter++] = ch2;
		}
		else if(ch2 == '(')
		{
			geciciayarlar[karakter] = '\0';
			ayarlar[satir] = atoi(geciciayarlar);
			karakter = 0;
			son++;
		}
		else if(ch2 == '\n')
		{
			satir++;
		}
	}
	fclose(fp2); 
}

void lig_ayarlar_yazdir()	//Lig ayarlarını ekrana yazdırır.
{
	printf("Lig ayarları şu şekildedir: \n");
	printf("Girilebilecek maksimum takım sayısı: %d\n", ayarlar[0]);
	printf("Galibiyet başına alınacak puan: %d\n", ayarlar[1]);
	printf("Beraberlik başına alınacak puan: %d\n", ayarlar[2]);
	printf("Mağlubiyet başına alınacak puan: %d\n", ayarlar[3]);
}

void mac_listesi_guncelle(char gecicimaclar[][4]) // mac_listesi_oku ve mac_listesi_girdial fonksiyonlarında toplam 2 kere aynı kodu yazmamak için oluşturulmuş bir fonksiyon.
{
	lig_sirala_takmaisim();
	char harf = 'A';
	int i = 0;
	for(harf, i; harf <= 'Z'; harf++, i++)
	{
		if(i == ayarlar[0])
		{
			break;
		}
		else if(gecicimaclar[0][0] == gecicimaclar[2][0])
		{
			printf(" (MAÇ HATASI!) - (BİR TAKIM KENDİSİ İLE MAÇ YAPAMAZ!) \n");
			break;
		}
		else if(gecicimaclar[0][0] > gecici_takmaismi)
		{
			printf(" (MAÇ HATASI!) - (%c takımı takımlar listesinde olmadığından '%c %c %c %c' skoru puan tablosuna işlenmeyecektir.) \n"
				, gecicimaclar[0][0], gecicimaclar[0][0], gecicimaclar[1][0], gecicimaclar[2][0], gecicimaclar[3][0]);
			break;
		}
		else if(gecicimaclar[2][0] > gecici_takmaismi)
		{
			printf(" (MAÇ HATASI!) - (%c takımı takımlar listesinde olmadığından '%c %c %c %c' skoru puan tablosuna işlenmeyecektir.) \n"
				, gecicimaclar[2][0], gecicimaclar[0][0], gecicimaclar[1][0], gecicimaclar[2][0], gecicimaclar[3][0]);
			break;
		}
		else if(oynanan_mac_test(gecicimaclar[0][0], gecicimaclar[2][0]) == 1 && gecicimaclar[0][0] == harf)
		{
			printf(" (MAÇ HATASI!) - (%c - %c takımları daha önceden %c'nın sahasında maç yaptığı için '%c %c %c %c' skoru puan tablosuna işlenmeyecektir.) \n"
				, gecicimaclar[0][0], gecicimaclar[2][0], gecicimaclar[0][0], gecicimaclar[0][0], gecicimaclar[1][0], gecicimaclar[2][0], gecicimaclar[3][0]);
			break;
		}
		else if(oynanan_mac_test(gecicimaclar[2][0], gecicimaclar[0][0]) == 1 && gecicimaclar[2][0] == harf)
		{
			printf(" (MAÇ HATASI!) - (%c - %c takımları daha önceden %c'nın sahasında maç yaptığı için '%c %c %c %c' skoru puan tablosuna işlenmeyecektir.) \n"
				, gecicimaclar[0][0], gecicimaclar[2][0], gecicimaclar[0][0], gecicimaclar[0][0], gecicimaclar[1][0], gecicimaclar[2][0], gecicimaclar[3][0]);
			break;
		}
		else if(gecicimaclar[0][0] == harf && gecicimaclar[0][0] != gecicimaclar[2][0]) 
		{
			takimlar[i].atilangol += atoi(gecicimaclar[1]);			// atoi fonksiyonu, char dizisini int'e atamak için.
			takimlar[i].yenilengol += atoi(gecicimaclar[3]);
			takimlar[i].oynananmac++;
			takimlar[i].averaj += atoi(gecicimaclar[1]) - atoi(gecicimaclar[3]);

			maclar[macsayisi].birinci_takim_adi = gecicimaclar[0][0];
			maclar[macsayisi].birinci_takim_gol_sayisi = atoi(gecicimaclar[1]);
			if(atoi(gecicimaclar[1]) > atoi(gecicimaclar[3]))
			{
				takimlar[i].galibiyet++;
				takimlar[i].puan += ayarlar[1];
			}
			else if(atoi(gecicimaclar[3]) > atoi(gecicimaclar[1]))
			{
				takimlar[i].maglubiyet++;
				takimlar[i].puan += ayarlar[3];
			}
			else if(atoi(gecicimaclar[1]) == atoi(gecicimaclar[3]))
			{
				takimlar[i].beraberlik++;
				takimlar[i].puan += ayarlar[2];
			}
		}
		else if(gecicimaclar[2][0] == harf && gecicimaclar[0][0] != gecicimaclar[2][0])
		{
			takimlar[i].atilangol += atoi(gecicimaclar[3]);
			takimlar[i].yenilengol += atoi(gecicimaclar[1]);
			takimlar[i].oynananmac++;
			takimlar[i].averaj += atoi(gecicimaclar[3]) - atoi(gecicimaclar[1]);
			maclar[macsayisi].ikinci_takim_adi = gecicimaclar[2][0];
			maclar[macsayisi].ikinci_takim_gol_sayisi = atoi(gecicimaclar[3]);

			if(atoi(gecicimaclar[3]) > atoi(gecicimaclar[1]))
			{
				takimlar[i].galibiyet++;
				takimlar[i].puan += ayarlar[1];
			}
			else if(atoi(gecicimaclar[1]) > atoi(gecicimaclar[3]))
			{
				takimlar[i].maglubiyet++;
				takimlar[i].puan += ayarlar[3];
			}
			else if(atoi(gecicimaclar[3]) == atoi(gecicimaclar[1]))
			{
				takimlar[i].beraberlik++;
				takimlar[i].puan += ayarlar[2];
			}
		}
	}
}

void mac_listesi_oku()
{
	char ch3;					//gecicimaclar[0][0]: 1. takım, gecicimaclar[1]: 1. takımın attığı gol sayısı,
	FILE *fp3 = fopen("maclar1.txt","r");		//gecicimaclar[2][0]: 2. takım, gecicimaclar[3]: 2. takımın attığı gol sayısı,
	int karakter = 0;
	int satir = 0;
	char gecicimaclar[4][4];
	while(!feof(fp3))
	{
		ch3 = getc(fp3);
		if(ch3 == ' ')
		{
			gecicimaclar[satir++][karakter] = '\0';
			karakter = 0;
		}
		else if(ch3 == '\n')
		{
			mac_listesi_guncelle(gecicimaclar);
			satir = 0;
			karakter = 0;
			macsayisi++;
			for(int i = 0; i < 4; i++){
				for(int j = 0; j < 4; j++){
					gecicimaclar[i][j] = ' ';
				}
			}
		}
		else
		{			
			gecicimaclar[satir][karakter++] = ch3;
		}
	}
}

void mac_listesi_yazdir()	//Maç listesini yazdırır.
{
	printf("Maç listesi okunuyor...\n");
	char harf = 'A';
	int i = 0;
	for(harf, i; harf <= 'Z'; harf++, i++)
	{
		printf("%c 'nın atılan gol= %d | yenilen gol= %d \n", harf, takimlar[i].atilangol, takimlar[i].yenilengol);
	}
}

void mac_listesi_girdial()	//Maç listesini girdi almak için.
{
	int karakter = 0;
	int satir = 0;
	char gecicimaclar[4][4];
	
	printf("Lütfen oynanmış bir maç skoru giriniz (A 1 B 2): ");
	scanf("%s %s %s %s", gecicimaclar[0], gecicimaclar[1], gecicimaclar[2], gecicimaclar[3]);	//gecicimaclar[0][0]: 1. takım, gecicimaclar[1]: 1. takımın attığı gol sayısı,
	getchar();													//gecicimaclar[2][0]: 2. takım, gecicimaclar[3]: 2. takımın attığı gol sayısı,
	printf("Giriş başarılı.");
	if(islower(gecicimaclar[0][0])) { gecicimaclar[0][0] = toupper(gecicimaclar[0][0]); }
	if(islower(gecicimaclar[2][0])) { gecicimaclar[2][0] = toupper(gecicimaclar[2][0]); }
	mac_listesi_guncelle(gecicimaclar);
	
}

int oynanan_mac_test(char takim1, char takim2)	//Maç daha önce oynandı mı? testini yapar.
{
	for(int i = 0; i < macsayisi; i++)
	{
		if(maclar[i].birinci_takim_adi == takim1 && maclar[i].ikinci_takim_adi == takim2)
		{
			return 1;
		}
	}
	return 0;
}

void lig_durumtablosu_yazdir()	//Puan durum tablosunu yazdırır.
{
	printf("Lig puan durum tablosu görüntüleniyor...\n");
	printf("%14s|", "Takma adı");
	printf("%20s|", "Takım");
	printf("%20s|", "Oynanan Maç");
	printf("%15s|", "Galibiyet");
	printf("%15s|", "Beraberlik");
	printf("%15s|", "Mağlubiyet");
	printf("%15s|", "Atılan gol");
	printf("%15s|", "Yenilen gol");
	printf("%15s|", "Averaj");
	printf("%15s|", "Puan");
	printf("\n");
	for(int i = 0; i < takimsayisi; i++)
	{
		printf("%3d.%9c|", (i+1), takimlar[i].takmaismi);
		printf("%19s|", takimlar[i].uzunismi);
		printf("%19d|", takimlar[i].oynananmac);
		printf("%15d|", takimlar[i].galibiyet);
		printf("%15d|", takimlar[i].beraberlik);
		printf("%14d|", takimlar[i].maglubiyet);
		printf("%14d|", takimlar[i].atilangol);
		printf("%15d|", takimlar[i].yenilengol);
		printf("%15d|", takimlar[i].averaj);
		printf("%15d|", takimlar[i].puan);
		printf("\n");
	}
}

void takimlar_standart_harf_guncelle()	//Takımlarını baş harflerini büyük olarak günceller.
{
	for(int satir = 0; satir < takimsayisi; satir++)
	{
		for(int karakter = 1; karakter < 12; karakter++)
		{
			takimlar[satir].uzunismi[0] = toupper(takimlar[satir].uzunismi[0]);
			if(takimlar[satir].uzunismi[karakter - 1] == ' ')
			{
				takimlar[satir].uzunismi[karakter] = toupper(takimlar[satir].uzunismi[karakter]);
			}
			else if(takimlar[satir].uzunismi[karakter - 1] != ' ')
			{
				takimlar[satir].uzunismi[karakter] = tolower(takimlar[satir].uzunismi[karakter]);
			}
		}
	}
}

void takimlar_buyuk_harf_guncelle()	//Takımları büyük harf olarak günceller.
{
	for(int satir = 0; satir < takimsayisi; satir++)
	{
		for(int karakter = 0; karakter < 12; karakter++)
		{
			takimlar[satir].uzunismi[karakter] = toupper(takimlar[satir].uzunismi[karakter]);
		}
	}
}

void takimlar_kucuk_harf_guncelle()	//Takımları küçük harf olarak günceller.
{
	for(int satir = 0; satir < takimsayisi; satir++)
	{
		for(int karakter = 0; karakter < 12; karakter++)
		{
			takimlar[satir].uzunismi[karakter] = tolower(takimlar[satir].uzunismi[karakter]);
		
		}
	}
}

void struct_yerdegistir(int a, int b)	//Puan tanlosuna takımları sıralama yaptırırken kullanılır.	
{
	takimlar[26] = takimlar[a];
	takimlar[a] = takimlar[b];
	takimlar[b] = takimlar[26];
}

void lig_sirala_puan()	//Puan tablosunu puana göre sıralar.
{
	for(int i = 0; i < takimsayisi; i++)
	{
		for(int j = i + 1; j < takimsayisi; j++)
		{
			if(takimlar[i].puan < takimlar[j].puan)
			{
				struct_yerdegistir(i, j);
			}
			else if(takimlar[i].puan == takimlar[j].puan)
			{
				if(takimlar[i].averaj < takimlar[j].averaj)
				{
					struct_yerdegistir(i, j);
				}
				else if(takimlar[i].averaj == takimlar[j].averaj)
				{
					if(takimlar[i].takmaismi > takimlar[j].takmaismi)
					{
						struct_yerdegistir(i, j);
					}
				}
			}
		}
	}
}

void lig_sirala_takmaisim()	//Puan tablosunu takma ada göre sıralar.
{
	for(int i = 0; i < takimsayisi; i++)
	{
		for(int j = i + 1; j < takimsayisi; j++)
		{
			if(takimlar[i].takmaismi > takimlar[j].takmaismi)
			{
				struct_yerdegistir(i, j);
			}
		}
	}
}

void lig_sirala_isim()	//Puan tablosunu takımın ilk harfine göre sıralar.
{
	for(int i = 0; i < takimsayisi; i++)
	{
		for(int j = i + 1; j < takimsayisi; j++)
		{
			if(takimlar[i].uzunismi[0] > takimlar[j].uzunismi[0])
			{
				struct_yerdegistir(i, j);
			}
		}
	}
}

void lig_puan_durumu_dosyaya_yazdir()	//Puan durum tablosunu puandurumu dosyasına yazdırır.
{
	FILE *fp = fopen("puantablosu.txt", "w");
	fprintf(fp, "%14s|", "Takma adı");
	fprintf(fp, "%20s|", "Takım");
	fprintf(fp, "%20s|", "Oynanan Maç");
	fprintf(fp, "%15s|", "Galibiyet");
	fprintf(fp, "%15s|", "Beraberlik");
	fprintf(fp, "%15s|", "Mağlubiyet");
	fprintf(fp, "%15s|", "Atılan gol");
	fprintf(fp, "%15s|", "Yenilen gol");
	fprintf(fp, "%15s|", "Averaj");
	fprintf(fp, "%15s|", "Puan");
	fprintf(fp, "\n");
	for(int i = 0; i < takimsayisi; i++)
	{
		fprintf(fp, "%3d.%9c|", (i+1), takimlar[i].takmaismi);
		fprintf(fp, "%19s|", takimlar[i].uzunismi);
		fprintf(fp, "%19d|", takimlar[i].oynananmac);
		fprintf(fp, "%15d|", takimlar[i].galibiyet);
		fprintf(fp, "%15d|", takimlar[i].beraberlik);
		fprintf(fp, "%14d|", takimlar[i].maglubiyet);
		fprintf(fp, "%14d|", takimlar[i].atilangol);
		fprintf(fp, "%15d|", takimlar[i].yenilengol);
		fprintf(fp, "%15d|", takimlar[i].averaj);
		fprintf(fp, "%15d|", takimlar[i].puan);
		fprintf(fp, "\n");
	}
	fclose(fp);
	printf("puantablosu.txt dosyası başarıyla güncellendi.");
}

