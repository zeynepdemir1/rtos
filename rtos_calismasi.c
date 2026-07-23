#include <stdint.h>
#include <stdio.h>

#define PARASUT_BITI 4
#define PARASUT_AC()  (port->tum_veriler |= (1<<PARASUT_BITI))
#define PARASUT_KAPAT()  (port->tum_veriler &= ~(1<<PARASUT_BITI))
#define PARASUT_TERSLE() (port->tum_veriler ^= (1<<PARASUT_BITI))

#define ERROR_BASLANGIC 0
#define ERROR_MASKE 0X0F
#define ERROR_OKU() ((port->tum_veriler >> ERROR_BASLANGIC)&ERROR_MASKE)
#define ERROR_TEMIZLE() (port->tum_veriler &= ~(ERROR_MASKE<<ERROR_BASLANGIC))
#define ERROR_YAZ(deger)  (ERROR_TEMIZLE(), port->tum_veriler |= ((deger&ERROR_MASKE)<<ERROR_BASLANGIC) )

#define SENSOR_BASLANGIC 5
#define SENSOR_MASKE 0X7FFFFFF
#define SENSOR_OKU() ((port->tum_veriler>>SENSOR_BASLANGIC) & SENSOR_MASKE)
#define SENSOR_TEMIZLE()  ((port->tum_veriler) &= ~(SENSOR_MASKE<<SENSOR_BASLANGIC))  
#define SENSOR_YAZ(sicaklik)  (SENSOR_TEMIZLE(),(port->tum_veriler) |= ((sicaklik&SENSOR_MASKE)<<SENSOR_BASLANGIC))


uint32_t bellek_alani;


union telemetriler{
    uint32_t tum_veriler;

    struct {
        uint32_t error: 4 ;
        uint32_t parasut: 1 ;
        uint32_t sensor:27 ;
    }bit_fields;
};

volatile union telemetriler *const port = (union telemetriler*)&bellek_alani;

int main(){
    
    printf("1. Rampa Durumu\n");
    printf("Ham Paket Degeri: %u\n\n", port->tum_veriler);

    SENSOR_YAZ(1024);
    printf("2. Sensor Verisi Eklendi\n");
    printf("Ham Paket Degeri: %u\n\n", port->tum_veriler);


    ERROR_YAZ(3);
    printf("3. Hata Kodu Eklendi\n");
    printf("Ham Paket Degeri: %u\n\n", port->tum_veriler);

    PARASUT_AC();
    printf("4. Parasut Acildi\n");
    printf("Ham Paket Degeri: %u\n\n", port->tum_veriler);


    printf("PAKET COZUMLEMESI\n");
    
    printf("Okunan Hata Kodu  : %u\n", ERROR_OKU());
    printf("Parasut Durumu    : %u\n", (port->tum_veriler >> PARASUT_BITI) & 1); 
    printf("Okunan Sensor Veri: %u\n", SENSOR_OKU());

    return 0;
}