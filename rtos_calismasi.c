#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

uint32_t bellek_alani;


union telemetriler{
    uint32_t tum_veriler;

    struct {
        uint32_t error: 4 ;
        uint32_t parasut: 1 ;
        uint32_t yukseklik: 12;
        uint32_t sicaklik: 8;
        uint32_t batarya: 7;
    }bit_fields;
};


volatile union telemetriler *const port = (union telemetriler*)&bellek_alani;

uint32_t sahte_barometre_oku(uint32_t eski_yukseklik){
    if(eski_yukseklik-150){
        return eski_yukseklik - 150;
    } return 0;

}



int main(){
 
    port->bit_fields.error = 0;
    port->bit_fields.yukseklik = 2000;
    port->bit_fields.sicaklik = 25; 
    port->bit_fields.batarya = 100;

    while(1){
        port->bit_fields.yukseklik=sahte_barometre_oku(port->bit_fields.yukseklik);
        printf("İrtifa: %d metre\n",port->bit_fields.yukseklik);

        if(port->bit_fields.yukseklik < 400){
            port->bit_fields.parasut = 1;
            printf("Paraşüt açılıyor!\n");

            break;
    
    }
        sleep(1);
    }


    printf("   Güncel Değerler\n");
    printf("Sıcaklık: %d\n",port->bit_fields.sicaklik);
    printf("Yükseklik: %d\n",port->bit_fields.yukseklik);
    printf("Batarya: %d\n",port->bit_fields.batarya);

    return 0;
}