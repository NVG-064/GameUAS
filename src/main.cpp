// TITLE \t\t\t\t\t\t
// PARAGHRAPH \t\t
// START \t

/* My concept about damage:
All attribute will be converted to power and life while battle to boss
1 magic = 2x power
1 defense = 3x life
1 potion = 3x power & 3x defense
*/

#include <iostream> // input ouput stream
#include <fstream> // to output the file to battleHistory.log
#include <string> // using for check string empty a.k.a variable_string_name.empty()
#include <unistd.h> // using for sleep() command
#define maxa 100 // for all struct that saving information will be maximied 100 match
using namespace std; // using standart namespace


int MAX = 100; // MAX life can be increased
int indexa = 0; // increment for saving history game
int i = 0; // increment for saving history game to file battleHistory.log

struct data{ // struct main information
    string nama;
    string karakter;
    string weapon;
    int gCoin;
}userInfo;

struct statistic{ // struct main statistic/attribute
    int life;
    int power;
    int defense;
    int magic;
    int potion;
}stat;

struct historyBattle{ // struct history battle
    // common information
    int battleId[maxa];
    string enemyName[maxa];
    string hasil[maxa];

    // detail information
    int totalDamageHero[maxa];
    int totalLifeHero[maxa];
    int totalDamageBoss[maxa];
    int totalLifeBoss[maxa];
    int lastLifeHero[maxa];
    int lastLifeBoss[maxa];
}history;

struct enemyBoss{ // contain boss
    string name[2] = {"The Boss of Knight Tree", "The Boss of Knight Pegasus"};
    int life[2] = {100, 700};
    int power[2] = {50, 500};
}boss;



string hasil(int hasil){ // string to output win or lose
    string state;
    if (hasil == 1){
        state = "Berhasil";
        return state;
    }
    else {
        state = "Gagal";
        return state;
    }
}

void coreUpgradeStatus(int gCoin, int statPower, int statMagic, int statDefense, int statPotion){
    char pilihanq2;

    system("cls");
    cout << "\n\n\tHarganya " << gCoin << " g. Yakin? [Y/N]\n\t";
    cin >> pilihanq2;
        
    if (pilihanq2 == 'Y'){
        userInfo.gCoin -= gCoin;

        stat.power += statPower;
        stat.magic += statMagic;
        stat.defense += statDefense;
        stat.potion += statPotion;
        cout << "\n\tPembelian berhasil\n";
        system("pause");

        if (userInfo.gCoin < 0){
            cout << "\n\tPembelian dibatalkan karena terdeteksi saldo tidak cukup\n";
            userInfo.gCoin += gCoin;

            stat.power -= statPower;
            stat.magic -= statMagic;
            stat.defense -= statDefense;
            stat.potion -= statPotion;
            sleep(2.5);
        }
    }

    else {
        cout << "\n\tPembelian dibatalkan\n";
        system("pause");
    }
    
    return;
}

void upgradeStatus(){ // to increase status/attribute/statistic
    int pilihanq;

    for (;;){
        system("cls");
        cout << "\t\t\t\t\t\tPOTION SHOP" << endl << endl;
        cout << "\tJumlah koin kamu: " << userInfo.gCoin << " g" << endl << endl;
        cout << "\tKamu bisa meningkatkan atributmu dengan membeli potion." << endl;
        cout << "\tPotion yang tersedia: " << endl;
        cout << "\t1. Normal potion (meningkatkan atribut potion sebanyak 10)" << endl;
        cout << "\t2. Special potion (meningkatkan atribut potion sebanyak 30)" << endl;
        cout << "\t3. Potion of magic (meningkatkan atribut magic sebanyak 20)" << endl;
        cout << "\t4. Potion of damage (meningkatkan atribut power sebanyak 40)" << endl;
        cout << "\t5. Potion of Mending (meningkatkan semua atribut sebanyak 50)" << endl << endl;
        cout << "\t6. Kembali ke Desa" << endl << endl;
        cout << "\tPilihan: ";
        cin >> pilihanq;

        // int gCoin, int statPower, int statMagic, int statDefense, int statPotion

        if (pilihanq == 1){
            coreUpgradeStatus(500, 0, 0, 0, 10);
        }

        else if (pilihanq == 2){
            coreUpgradeStatus(1000, 0, 0, 0, 30);
        }

        else if (pilihanq == 3){
            coreUpgradeStatus(625, 0, 20, 0, 0);
        }

        else if (pilihanq == 4){
            coreUpgradeStatus(625, 40, 0, 0, 0);
        }

        else if (pilihanq == 5){
            coreUpgradeStatus(2000, 50, 50, 50, 50);
        }

        else if (pilihanq == 6){
            return;
        }
    }
}

void coreBattleProcess(int pilih, int gCoin, int maxLife, int statPower, int statMagic, int statDefense, int statPotion){
    int damageHero, lastLife, lifeHero, lifeBoss, resultBool;
    string resultBattle;

    system("cls");
    cout << "\t\t\t\t\t\t\tINFORMASI BOSS" << endl << endl;
    cout << "\tNama Boss\t: " << boss.name[pilih] << endl;
    cout << "\tLife\t\t: " << boss.life[pilih] << endl;
    cout << "\tDamage Boss\t: " << boss.power[pilih] << endl << endl << endl;
    cout << "\t\t\t\t\t\tLOADING, HARAP TUNGGU" << endl;
    sleep(10);
    cout << "\t\t\t\t\t\tTekan apapun untuk melanjutkan" << endl;
    system("pause");

    system("cls");
    damageHero = (stat.power + (2*stat.magic) + (3*stat.potion)); // total damage hero
    lifeHero = (stat.life + (3*stat.defense) + ((3*stat.potion)*3)); // total life hero
    lastLife = (lifeHero - boss.power[pilih]); // last life hero
    lifeBoss = (boss.life[pilih] - damageHero); // last life boss

    if (lifeBoss <= 0){
        resultBool = 1;

        userInfo.gCoin += gCoin;
        MAX += maxLife;
        stat.power += statPower;
        stat.magic += statMagic;
        stat.defense += statDefense;
        stat.potion += statPotion;
    }

    else {
        resultBool = 0;
    }
                
    // to save history
    history.battleId[indexa] = 1604064 + indexa;
    history.enemyName[indexa] = boss.name[pilih];
    history.hasil[indexa] = hasil(resultBool);

    // to save history
    history.totalLifeHero[indexa] = lifeHero;
    history.totalDamageHero[indexa] = damageHero;
    history.lastLifeHero[indexa] = lastLife;
    history.totalLifeBoss[indexa] = boss.life[pilih];
    history.totalDamageBoss[indexa] = boss.power[pilih];
    history.lastLifeBoss[indexa] = lifeBoss;
                
    indexa++;

    cout << "\n\n\n\n\n\t\t\t\t\tSEDANG BATTLE" << endl;
    cout << "\t\t\t\t\tMEMBUTUHKAN WAKTU SEKITAR 15 DETIK" << endl;
    sleep(15);
    system("pause");
                
    system("cls");
    resultBattle = hasil(resultBool);
    cout << "\n\n\n\n\n\t\t\t\t\tKamu " << resultBattle << endl;
    cout << "\t\t\t\tTekan tombol apapun untuk kembali ke Desa" << endl;
    system("pause");

    return;
}

void battle(){ // to battle
    int pilih;
    int gCoin, maxLife, statPower, statMagic, statDefense, statPotion;

    for (;;){
        system("cls");
        cout << "\t\t\t\t\t\tBERTEMPUR" << endl << endl;
        cout << "\tPIlih lawan" << endl;
        cout << "\t1. " << boss.name[0] << endl;
        cout << "\t2. " << boss.name[1] << endl << endl;
        cout << "\t3. Kembali ke Desa" << endl << endl;
        cout << "\tMasukkan pilihanmu: ";
        cin >> pilih;

        if (pilih == 1){
            gCoin = 125;
            maxLife = 128;
            statPower = 22;
            statMagic = 13;
            statDefense = 14;
            statPotion = 8;
            coreBattleProcess(pilih-1, gCoin, maxLife, statPower, statMagic, statDefense, statPotion);

            return;
        }

        else if (pilih == 2){
            gCoin = 575;
            maxLife = 410;
            statPower = 50;
            statMagic = 42;
            statDefense = 30;
            statPotion = 30;
            coreBattleProcess(pilih-1, gCoin, maxLife, statPower, statMagic, statDefense, statPotion);

            return;
        }

        else if (pilih == 3){
            return;
        }

        else {
            // you're stuck on the loop
        }
    }
}

void saveGame(){
    system("cls");
    char pilih;
    cout << "\t\t\t\t\t\tKONFIRMASI" << endl << endl;
    cout << "\n\tApa kamu ingin menyimpan data game kamu? [Y/N]" << endl;
    cout << "\t";
    cin >> pilih;

    ofstream file;

    switch(pilih){
        case 'Y':
            file.open("gameHistory.log");

            file << "\t\tStatistik dasar\n\nNama\t\t\t: " << userInfo.nama << "\nKarakter\t\t: " << userInfo.karakter << "\nSenjata\t\t\t: " << userInfo.weapon << "\nKoin\t\t\t: " << userInfo.gCoin << " g";
            file << "\n\n\t\tStatistik atribut\n\nLife\t\t\t: " << stat.life << "\nPower\t\t\t: " << stat.power << "\nMagic\t\t\t: " << stat.magic << "\nDefense\t\t\t: " << stat.defense << "\nPotion\t\t\t: " << stat.potion << "\n\n";

            file << "\n\n================================================================\n\n";

            while(!history.hasil[i].empty()){
                file << "\t\tRiwayat Battle\n\nBattle ID\t\t: " << history.battleId[i] << "\nNama boss\t\t: " << history.enemyName[i] << "\nHasil battle\t\t: " << history.hasil[i];

                file << "\n\n\t\tHasil Detail Battle\n\nTotal life kamu\t\t: " << history.totalLifeHero[i] << "\nTotal power kamu\t: " << history.totalDamageHero[i] << "\nSisa life kamu\t\t: " << history.lastLifeHero[i] << "\nTotal life boss\t\t: " << history.totalLifeBoss[i] << "\nTotal power boss\t: " << history.totalDamageBoss[i] << "\nSisa life boss\t\t: " << history.lastLifeBoss[i];

                file << "\n\n================================================================\n\n";

                i++;
                cout << "\n\n";
            }

            file.close();

            cout << "\n\tBerhasil disimpan" << endl;
            break;
        
        case 'N':
            break;
        
        default:
            return saveGame();
    }
    
    cout << "\n\n\tTerima kasih sudah bermain Game Lilo dan Lily :)" << endl;
}

void statusCheck(){
    system("cls");

    cout << "\t\t\t\t\t\tSTATUS" << endl << endl;
    cout << "\tLife\t: " << stat.life << endl;
    cout << "\tPower\t: " << stat.power << endl;
    cout << "\tMagic\t: " << stat.magic << endl;
    cout << "\tDefense\t: " << stat.defense << endl;
    cout << "\tPotion\t: " << stat.potion << endl << endl;
    system("pause");
}

int weaponStats(){
    int stats;
    if (userInfo.weapon == "Sword"){
        stats = 2;
        return stats;
    }
    else if (userInfo.weapon == "Axe"){
        stats = 2;
        return stats;
    }
    else if (userInfo.weapon == "Arrow"){
        stats = 2;
        return stats;
    }
    else if (userInfo.weapon == "Magic Wand"){
        stats = 2;
        return stats;
    }
    else {
        return stats = 0;
    } 
}

void characterWeapon(){
    string weapon[4] = {"Sword", "Axe", "Arrow", "Magic Wand"};
    int pilihanku;

    system("cls");
    cout << "\t\t\t\t\t\tALAT PERSENJATAAN" << endl << endl;
    cout << "\tHalo " << userInfo.nama << ".\n\tPilih alat persenjataan kamu: " << endl;
    cout << "\t1. " << weapon[0] << endl;
    cout << "\t2. " << weapon[1] << endl;
    cout << "\t3. " << weapon[2] << endl;
    cout << "\t4. " << weapon[3] << endl;
    cout << "\n\t";
    cin >> pilihanku;

    if ((pilihanku > 0) && (pilihanku <= 4)) userInfo.weapon = weapon[pilihanku-1];
    else return characterWeapon();

    cout << "\n\n\tWah, pilihan yang bagus! Tekan tombol apapun untuk melanjutkan" << endl << endl;
    system("pause");

    return;
}

void nameInput(){
    string nama;

    system("cls");
    cout << "\t\t\t\t\t\tUSERNAME" << endl << endl;
    cout << "\n\tMasukkan username kamu: ";
    getline(cin, nama);

    if (nama.empty()) return nameInput();
    else userInfo.nama = nama;

    return;
}

void characterSelect(){
    string character[2] = {"Lilo", "Lily"};
    int pilih;

    system("cls");
    cout << "\t\t\t\t\t\tKARAKTER" << endl << endl;
    cout << "\tPilih karakter: " << endl;
    cout << "\t1. " << character[0] << endl;
    cout << "\t2. " << character[1] << endl << endl;
    cout << "\t";
    cin >> pilih;

    if ((pilih > 0) && (pilih <= 2)) userInfo.karakter = character[pilih-1];
    else return characterSelect();

    return;
}

void setWelcome(){
    system("cls");
    cout << "========================================================================================================================" << endl;
	cout << "   sssss            Ms                                   hh        nhssyys             yy                               " << endl;
	cout << "  mm        sssyo   Ms  ossyyo    yosysyysyy    sssyso  OMysO      Mo    sN   sssyyo  OMdsO  sssyyo   ysosyo    osso    " << endl;
	cout << "   ydhs    No   my  Ms      oM   Nh   Nd   dm       Nh   Ms        Mo     Nh      hN   Ny        dm  oM    Ms  oo  yo   " << endl;
	cout << "      oN   Msoooso  Ms   hssyM   Ns   mh   yN   hssoNd   Ms        Mo     My  hysohN   Ny    hysodN  oM    Ns  os  so   " << endl;
	cout << "       Nh  No       Ms  Ms  sM   Ns   mh   yN  dd   md   Mo        My    my  Ms   hN   mh   Ms   dN  oM    Ns   ossso   " << endl;
	cout << "   sssss    ossoo   Ms   ssoso   Ns   mh   yN   ososoo    sss      oooooo     osssso    sss  osssoo  os    os      oo   " << endl;
	cout << "                                                                                                                osso    " << endl;
	cout << "========================================================================================================================" << endl;
	cout << endl;
    cout << "\t\t\t\t\t\tdi Game Lilo dan Lily" << endl << endl;
    cout << "\t\t\t\t\tTekan tombol apapun untuk melanjutkan" << endl << endl;

    system("pause");
}

int main(){
    int pilihan;
    setWelcome();
    characterSelect();
    nameInput();
    characterWeapon();

    userInfo.gCoin = 1000;

    stat.life = 100;
    stat.power = 10 + weaponStats();
    stat.magic = 7 + weaponStats();
    stat.defense = 5;
    stat.potion = 25;

    for (;;){
        system("cls");

        cout << "\t\t\t\t\t\tDesa Universitas Esa Unggul" << endl << endl;
        cout << "\t1. Cek status" << endl;
        cout << "\t2. Bertempur" << endl;
        cout << "\t3. Atur nyawa menjadi penuh" << endl;
        cout << "\t4. Tingkatkan status" << endl << endl;
        cout << "\t5. Keluar dari game" << endl;
        cout << "\n\n\tMasukkan pilihanmu: ";
        cin >> pilihan;

        switch(pilihan){
            case 1:
                statusCheck();
                break;
            
            case 2:
                battle();
                break;

            case 3:
                stat.life = MAX;
                cout << "\n\n\tBerhasil!" << endl;
                system("pause");
                break;

            case 4:
                upgradeStatus();
                break;

            case 5:
                saveGame();
                return 0;
        }

    }
}