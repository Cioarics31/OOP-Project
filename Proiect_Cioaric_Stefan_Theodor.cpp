#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::ostream;
using std::istream;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::fstream;
using std::vector;

enum zonaCursor { ss = 1, sj, ds, dj, c }; //stanga sus, stanga jos, dreapta sus, dreapta jos, centru
class ScriereCSV {
public:
	virtual void scrieInFisier(ofstream& f) = 0;
};
class ProfilBaza :public ScriereCSV {
private:
	const int nrAccesari;
	int clickStg;
	int clickDr;
	int nrTasteApasate;
	float* durataApasareTasta;
	static string adresaIP;
	static int contorAcc;
	zonaCursor zona;
public:
	void scrieInFisier(ofstream& f) {
		f << "\n";
		f << clickStg << ", ";
		f << clickDr << ", ";
		switch (zona) {
		case 1:
			f << "Stanga sus, ";
			break;
		case 2:
			f << "Stanga jos, ";
			break;
		case 3:
			f << "Dreapta sus, ";
			break;
		case 4:
			f << "Dreapta jos, ";
			break;
		case 5:
			f << "Centru, ";
			break;
		default:
			f << "nu are zona cursor, ";
			break;
		}
		f << nrTasteApasate << ", ";
		f << adresaIP << ", ";
	}
	void citesteDinFisier(ifstream& f) {
		f >> clickStg;
		f >> clickDr;
		int zon;
		f >> zon;
		zona = (zonaCursor)zon;
		/*switch (zon) {
		case 1:
			zona = ss;
		case 2:
			zona = sj;
			break;
		case 3:
			zona = ds;
			break;
		case 4:
			zona = dj;
			break;
		case 5:
			zona = c;
			break;
		}*/
		f >> nrTasteApasate;
		durataApasareTasta = new float[nrTasteApasate];
		for (int i = 0; i < nrTasteApasate; i++) {
			f >> durataApasareTasta[i];
		}
	}
	int getStg() {
		return this->clickStg;
	}
	void setStg(int nrStg) {
		this->clickStg = nrStg;
	}
	int getDr() {
		return this->clickDr;
	}
	void setDr(int nrDr) {
		this->clickDr = nrDr;
	}
	zonaCursor getZona() {
		return this->zona;
	}
	void setZona(zonaCursor zona) {
		this->zona = zona;
	}
	int getNrTasteApasate() {
		return this->nrTasteApasate;
	}
	void setNrTasteApasate(int nrTasteApasate, float* durataApasareTasta) {
		if (nrTasteApasate > 0) {
			this->nrTasteApasate = nrTasteApasate;
			if (this->durataApasareTasta != NULL) {
				delete[] this->durataApasareTasta;
			}
			this->durataApasareTasta = new float[nrTasteApasate];
			for (int i = 0; i < nrTasteApasate; i++) {
				this->durataApasareTasta[i] = durataApasareTasta[i];
			}
		}
	}
	float* getDurataApasareTaste() {
		return this->durataApasareTasta;
	}
	string getAdresaIP() {
		return this->adresaIP;
	}
	int getNrAccesari() {
		return this->nrAccesari;
	}
	ProfilBaza() :nrAccesari(contorAcc++) {
		this->clickStg = 0;
		this->clickDr = 0;
		this->zona = zonaCursor(0);
		this->nrTasteApasate = 0;
		this->durataApasareTasta = NULL;
	}
	ProfilBaza(int clickStg, int clickDr, zonaCursor zona, int nrTasteApasate, float* durataApasareTasta) :nrAccesari(contorAcc++) {
		this->clickStg = clickStg;
		this->clickDr = clickDr;
		this->zona = zona;
		this->nrTasteApasate = nrTasteApasate;
		this->durataApasareTasta = new float[this->nrTasteApasate];
		for (int i = 0; i < this->nrTasteApasate; i++)
			this->durataApasareTasta[i] = durataApasareTasta[i];
	}
	ProfilBaza(const ProfilBaza& prof) :nrAccesari(contorAcc++) {
		this->clickStg = prof.clickStg;
		this->clickDr = prof.clickDr;
		this->zona = prof.zona;
		this->nrTasteApasate = prof.nrTasteApasate;
		this->durataApasareTasta = new float[this->nrTasteApasate];
		for (int i = 0; i < this->nrTasteApasate; i++)
			this->durataApasareTasta[i] = prof.durataApasareTasta[i];
	}
	ProfilBaza& operator=(const ProfilBaza& prof) {
		if (this != &prof)
		{
			this->clickStg = prof.clickStg;
			this->clickDr = prof.clickDr;
			this->zona = prof.zona;
			this->nrTasteApasate = prof.nrTasteApasate;
			this->durataApasareTasta = new float[this->nrTasteApasate];
			for (int i = 0; i < this->nrTasteApasate; i++)
				this->durataApasareTasta[i] = prof.durataApasareTasta[i];
		}
		return *this;
	}
	friend istream& operator>>(istream& in, ProfilBaza& prof) {
		cout << "Numar click-uri stanga: ";
		in >> prof.clickStg;
		cout << "Numar click-uri dreapta: ";
		in >> prof.clickDr;
		cout << "Zona cursor (valoare de la 1 la 5): ";
		int opt, val = 0;
		in >> opt;
		if (opt < 1 || opt >5) {
			do {
				cout << "\nNu ati introdus o valoare corespunzatoare! Introduceti din nou Zona cursor, cu o valoare de la 1 la 5: ";
				in >> opt;
				if (opt >= 1 && opt <= 5)
					val = 1;
			} while (val == 0);
		}
		prof.zona = zonaCursor(opt);
		cout << "Numarul de taste apasate: ";
		in >> prof.nrTasteApasate;
		cout << "Durata de apasare a tastelor: ";
		if (prof.durataApasareTasta != NULL)
			delete[] prof.durataApasareTasta;
		prof.durataApasareTasta = new float[prof.nrTasteApasate];
		for (int i = 0; i < prof.nrTasteApasate; i++)
			in >> prof.durataApasareTasta[i];
		cout << '\n';
		return in;
	}
	friend ostream& operator<<(ostream& out, const ProfilBaza& prof) {
		out << "Numar accesari= " << prof.nrAccesari << endl;
		out << "Numar click-uri stanga= " << prof.clickStg << endl;
		out << "Numar click-uri dreapta= " << prof.clickDr << endl;
		switch (prof.zona) {
		case 1:
			out << "Zona cursor: Stanga sus\n";
			break;
		case 2:
			out << "Zona cursor: Stanga jos\n";
			break;
		case 3:
			out << "Zona cursor: Dreapta sus\n";
			break;
		case 4:
			out << "Zona cursor: Dreapta jos\n";
			break;
		case 5:
			out << "Zona cursor: Centru\n";
			break;
		default:
			out << "Utilizatorul este neinitializat, deci nu are zona cursor\n";
			break;
		}
		out << "Numar taste apasate= " << prof.nrTasteApasate << endl;
		out << "Durata de apasare a tastelor: ";
		if (prof.durataApasareTasta != NULL)
		{
			for (int i = 0; i < prof.nrTasteApasate; i++)
				out << prof.durataApasareTasta[i] << " ";
		}
		else out << "Nu au fost apasate taste!";
		out << endl;
		out << "Adresa IP: " << prof.adresaIP << endl;
		out << endl;
		return out;
	}
	ProfilBaza operator++() {
		this->clickStg++;
		return *this;
	}
	ProfilBaza operator++(int) {
		ProfilBaza aux;
		aux = *this;
		this->clickStg++;
		return aux;
	}
	bool operator==(const ProfilBaza& prof) {
		return this->clickStg == prof.clickStg && this->clickDr == prof.clickDr && this->nrTasteApasate == prof.nrTasteApasate;
	}
	bool operator>(const ProfilBaza& prof) {
		return this->nrTasteApasate > prof.nrTasteApasate;
	}
	ProfilBaza operator-(const ProfilBaza& prof) {
		ProfilBaza aux(*this);
		aux.clickStg = this->clickStg - prof.clickStg;
		return aux;
	}
	ProfilBaza operator/(const ProfilBaza& prof) {
		ProfilBaza aux(*this);
		aux.clickDr = this->clickDr / prof.clickDr;
		return aux;
	}
	static void adaugaProfilInVector(ProfilBaza*& vector, const ProfilBaza& obiect, int& dimens) {
		ProfilBaza* aux;
		aux = new ProfilBaza[dimens + 1];
		for (int i = 0; i < dimens; i++)
		{
			aux[i] = vector[i];
		}
		aux[dimens++] = obiect;
		if (vector != NULL)
			delete[]vector;
		vector = aux;
	}
	~ProfilBaza() {
		if (this->durataApasareTasta != NULL)
			delete[] this->durataApasareTasta;
	}
};
string ProfilBaza::adresaIP = "48.101.181.247"; //toti utilizatorii au aceeasi adresa IP(spre ex: acceseaza membrii familiei conectati la aceeasi retea)
int ProfilBaza::contorAcc = 1;
class ProfilAdv :public ProfilBaza {
private:
	bool verifEmail;
	char* email;
	int nrShift;
	int idUser;
	string username;
public:
	void scrieInFisier(ofstream& f) {
		ProfilBaza::scrieInFisier(f);
		f << username << ", ";
		f << verifEmail << ", ";
		f << email << ", ";
		f << nrShift << ", ";
	}
	bool getVerifEmail() {
		return this->verifEmail;
	}
	void setVerifEmail(bool ver) {
		this->verifEmail = ver;
	}
	char* getEmail() {
		return this->email;
	}
	void setEmail(const char* email) {
		if (email != NULL)
		{
			this->email = new char[strlen(email) + 1];
			strcpy_s(this->email, strlen(email) + 1, email);
		}
	}
	int getNrShift() {
		return this->nrShift;
	}
	void setNrShift(int nrShift) {
		this->nrShift = nrShift;
	}
	string getUsername() {
		return this->username;
	}
	void setUsername(string username) {
		this->username = username;
	}
	ProfilAdv() :ProfilBaza() {
		this->idUser = 0;
		this->username = "neinitializat";
		this->verifEmail = 0;
		this->email = NULL;
		this->nrShift = 0;
	}
	ProfilAdv(int idUser, string username, bool verifEmail, const char* email, int nrShift, int clickStg, int clickDr, zonaCursor zona, int nrTasteApasate, float* durataApasareTasta) :ProfilBaza(clickStg, clickDr, zona, nrTasteApasate, durataApasareTasta) {
		this->idUser = idUser;
		this->username = username;
		this->verifEmail = verifEmail;
		if (email != NULL)
		{
			this->email = new char[strlen(email) + 1];
			strcpy_s(this->email, strlen(email) + 1, email);
		}
		else
			this->email = NULL;
		this->nrShift = nrShift;
	}
	ProfilAdv(const ProfilAdv& prof) :ProfilBaza(prof) {
		this->idUser = prof.idUser;
		this->verifEmail = prof.verifEmail;
		if (prof.email != NULL)
		{
			this->email = new char[strlen(prof.email) + 1];
			strcpy_s(this->email, strlen(prof.email) + 1, prof.email);
		}
		else
			this->email = NULL;
		this->nrShift = prof.nrShift;
		this->username = prof.username;
	}
	ProfilAdv& operator=(const ProfilAdv& prof) {
		if (this != &prof)
		{
			(ProfilBaza)*this = (ProfilBaza)prof;
			ProfilBaza::operator=(prof);
			this->idUser = prof.idUser;
			this->verifEmail = prof.verifEmail;
			this->username = prof.username;
			if (prof.email != NULL)
			{
				this->email = new char[strlen(prof.email) + 1];
				strcpy_s(this->email, strlen(prof.email) + 1, prof.email);
			}
			this->nrShift = prof.nrShift;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const ProfilAdv& prof) {
		out << "Profil avansat:\n";
		out << "ID Utilizator:" << prof.idUser << endl;
		out << "Nume utilizator:" << prof.username << endl;
		out << ProfilBaza(prof);
		out << "Status verificare email (1->verificat/0->neverificat): " << prof.verifEmail << endl;
		if (prof.email != NULL) {
			out << "Adresa de e-mail: " << prof.email << '\n';
		}
		else cout << "Adresa de e-mail inexistenta\n";
		out << "Numarul de apasari a tastei Shift= " << prof.nrShift << endl;
		out << endl;
		return out;
	}
	friend istream& operator>>(istream& in, ProfilAdv& prof) {
		in >> (ProfilBaza&)prof;
		cout << "Introduceti ID utilizator:";
		in >> prof.idUser;
		cout << "Introduceti numele de utilizator:";
		in >> prof.username;
		cout << "Introduceti statusul verificarii adresei de email(1 pt verificat, 0 pt neverificat): ";
		in >> prof.verifEmail;
		cout << "Introduceti adresa de email: ";
		char buffer[50]; // joaca rol de buffer
		cin.get();
		cin.getline(buffer, 50);
		prof.email = new char[strlen(buffer) + 1];
		strcpy_s(prof.email, strlen(buffer) + 1, buffer);
		cout << "Introduceti numarul de apasari a tastei Shift: ";
		in >> prof.nrShift;
		return in;
	};
	ProfilAdv operator+(const ProfilAdv& prof) {
		ProfilAdv aux(*this);
		aux.nrShift = this->nrShift + prof.nrShift;
		return aux;
	}
	ProfilAdv operator--() {
		this->nrShift--;
		return *this;
	}
	ProfilAdv operator--(int) {
		ProfilAdv aux;
		aux = *this;
		this->nrShift--;
		return aux;
	}
	ProfilAdv operator*=(const ProfilAdv& prof) {
		this->nrShift *= prof.nrShift;
		return *this;
	}
	ProfilAdv operator+=(const ProfilAdv& prof) {
		this->nrShift += prof.nrShift;
		return *this;
	}
	ProfilAdv operator*(const ProfilAdv& prof) {
		ProfilAdv aux(*this);
		aux.nrShift = this->nrShift * prof.nrShift;
		return aux;
	}
	static void adaugaProfilAdvInVector(ProfilAdv*& vector, const ProfilAdv& obiect, int& dimens) {
		ProfilAdv* aux;
		aux = new ProfilAdv[dimens + 1];
		for (int i = 0; i < dimens; i++)
		{
			aux[i] = vector[i];
		}
		aux[dimens] = obiect;
		dimens++;
		if (vector != NULL)
			delete[]vector;
		vector = aux;
	}
	~ProfilAdv() {
		if (this->email != NULL)
			delete this->email;
	}
};
class DateExtra :public ScriereCSV {
private:
	string sistemOperare;
	int vechime;
	float ratie;
public:
	void scrieInFisier(ofstream& f) {
		f << sistemOperare << ", ";
		f << vechime << ", ";
		f << ratie << ", ";
	}
	string getSistemOperare() {
		return this->sistemOperare;
	}
	void setSistemOperare(string sistemOperare) {
		this->sistemOperare = sistemOperare;
	}
	int getVechime() {
		return this->vechime;
	}
	void setVechime(int vechime) {
		this->vechime = vechime;
	}
	float getRatie() {
		return this->ratie;
	}
	void setRatie(float ratie) {
		this->ratie = ratie;
	}
	DateExtra() {
		sistemOperare = "inexistnt";
		vechime = 0;
		ratie = 0;
	}
	DateExtra(string sistemOperare, int vechime, float ratie) {
		this->sistemOperare = sistemOperare;
		this->vechime = vechime;
		this->ratie = ratie;
	}
	DateExtra(const DateExtra& data) {
		this->sistemOperare = data.sistemOperare;
		this->vechime = data.vechime;
		this->ratie = data.ratie;
	}
	DateExtra& operator=(const DateExtra& data) {
		if (this != &data)
		{
			this->sistemOperare = data.sistemOperare;
			this->vechime = data.vechime;
			this->ratie = data.ratie;
		}
		return *this;
	}
	friend istream& operator>>(istream& in, DateExtra& data) {
		cout << "Sistem de Operare: ";
		in >> data.sistemOperare;
		cout << "Vechimea utilizatorului, exprimata in zile: ";
		in >> data.vechime;
		cout << "Ratia utilizatorului(raport realizat intre download si upload) :";
		in >> data.ratie;
		cout << '\n';
		return in;
	}
	friend ostream& operator<<(ostream& out, DateExtra& data) {
		out << "Sistem de Operare: " << data.sistemOperare << endl;
		out << "Vechimea utilizatorului, exprimata in zile: " << data.vechime << endl;
		out << "Ratia utilizatorului(raport realizat intre download si upload) :" << data.ratie << endl;
		out << '\n';
		return out;
	}
	DateExtra operator+=(const DateExtra& data) {
		this->ratie += data.ratie;
		return *this;
	}
	DateExtra operator-(const DateExtra& data) {
		DateExtra aux(*this);
		aux.ratie = this->ratie - data.ratie;
		return aux;
	}
	bool operator>(const DateExtra& data) {
		return this->vechime > data.vechime;
	}
	DateExtra operator--() {
		this->vechime--;
		return *this;
	}
	DateExtra operator--(int) {
		DateExtra aux;
		aux = *this;
		this->vechime--;
		return aux;
	}
	DateExtra operator/=(const DateExtra& data) {
		this->ratie /= data.ratie;
		return *this;
	}
	static void adaugaDateInVector(DateExtra*& vector, const DateExtra& obiect, int& dimens) {
		DateExtra* aux;
		aux = new DateExtra[dimens + 1];
		for (int i = 0; i < dimens; i++)
		{
			aux[i] = vector[i];
		}
		aux[dimens++] = obiect;
		if (vector != NULL)
			delete[]vector;
		vector = aux;
	}
};
template<class T>
class Detalii {
	T nrClick;
	string modCopiere;//meniu|scurtaturi|mix
	float durataActiv; //masurata in secunde
public:
	Detalii(T nrClick, string modCopiere, float durataActiv) {
		this->nrClick = nrClick;
		this->modCopiere = modCopiere;
		this->durataActiv = durataActiv;
	}
	friend ostream& operator<<(ostream& out, const Detalii& det) {
		out << "A avut o diferenta de clickuri= " << det.difClick << endl;
		out << "Copiaza/decupeaza folosind: " << det.modCopiere << endl;
		out << "Durata activitate " << det.durataActiv << endl;
		return out;
	}
	T getNrClick() {
		return this->nrClick;
	}
	void setNrClick(T nrClick) {
		this->nrClick = nrClick;
	}
	string getModCopiere() {
		return modCopiere;
	}
	void setModCopiere(string modCopiere) {
		this->modCopiere = modCopiere;
	}
	float getDurataActiv() {
		return this->durataActiv;
	}
	void setDurataActiv(float durataActiv) {
		this->durataActiv = durataActiv;
	}
	T operator-(const Detalii& det) {
		return this->nrClick - det.nrClick;
	}
};
void Meniu()
{
	cout << "\tMeniu!" << endl;
	cout << "\tUtilizati cifra corespunzatoare pentru a accesa optiunea dorita!" << endl;
	cout << "\t1.Afisati utilizatorii de baza existenti si care dintre ei coincid cu sesiunea citita din fisier." << endl;
	cout << "\t2.Introduceti un nou utilizator de baza si gasiti echivalentul." << endl;
	cout << "\t3.Afisati detalii avansate ale profilului cautat." << endl;
	cout << "\t4.Introduceti detalii privind modul de lucru al utilizatorului introdus si afisati diferenta intre numarul de click-uri stanga si dreapta." << endl;
	cout << "\t5.Verificati getterii pentru profilele deja initializate." << endl;
	cout << "\t6.Salvati un profil la alegere intr-un fisier. Datele vor fi salvate si separate prin simbolul ',' !" << endl;
	cout << "\t7.Salvati un profil complet la alegere intr-un fisier. Datele vor fi salvate si separate prin simbolul ',' ! " << endl;
	cout << "\t8.Introduceti datele complete pentru un profil." << endl;
}
void main()
{
	int nB = 0;
	ProfilBaza* vectorProfilBase = new ProfilBaza[nB];
	ProfilBaza prof0;
	ProfilBaza prof1(62, 14, c, 3, new float[3] {4.2f, 9.7f, 1.2f});
	ProfilBaza prof2(prof1);
	ProfilBaza prof3;
	prof3 = prof1;
	ProfilBaza prof4(22, 33, ds, 4, new float[4] {4.2f, 9.7f, 1.2f, 0.2f});
	ProfilBaza::adaugaProfilInVector(vectorProfilBase, prof0, nB);
	ProfilBaza::adaugaProfilInVector(vectorProfilBase, prof1, nB);
	ProfilBaza::adaugaProfilInVector(vectorProfilBase, prof2, nB);
	ProfilBaza::adaugaProfilInVector(vectorProfilBase, prof3, nB);
	ProfilBaza::adaugaProfilInVector(vectorProfilBase, prof4, nB);
	ProfilAdv profad0;
	ProfilAdv profad1(245, "Zhizu", 1, "hamham@pisica.com", 44, 62, 14, c, 3, new float[3] {4.2f, 9.7f, 1.2f});
	ProfilAdv profad2;
	profad2 = profad1;
	//cout << profad2;
	//profad2 += profad1;
	//cout << profad2;
	//profad2 *= profad1;
	//cout << profad2;
	//profad2 = profad2 * profad1;
	//cout << profad2;
	ProfilAdv profad3(8212, "Haki", 0, "baucicabau@bautu.esti", 823, 1002, 9287, dj, 10, new float[10] {1.1f, 2.9f, 9.0f, 5.2f, 11.2f, 34.21f, 84.23f, 100.21f, 921.12f, 5.2f});
	ProfilAdv profad4(profad3);
	int nA = 0;
	ProfilAdv* vectorProfilAdv = new ProfilAdv[nB];
	ProfilAdv::adaugaProfilAdvInVector(vectorProfilAdv, profad0, nA);
	ProfilAdv::adaugaProfilAdvInVector(vectorProfilAdv, profad1, nA);
	ProfilAdv::adaugaProfilAdvInVector(vectorProfilAdv, profad2, nA);
	ProfilAdv::adaugaProfilAdvInVector(vectorProfilAdv, profad3, nA);
	ProfilAdv::adaugaProfilAdvInVector(vectorProfilAdv, profad4, nA);
	//cout << vectorProfilAdv[2];
	//vectorProfilAdv[2] += vectorProfilAdv[1];
	//vectorProfilAdv[2] *= vectorProfilAdv[1];
	//cout << vectorProfilAdv[2];
	DateExtra data0;
	DateExtra data1("iOS", 5, 6.2f);
	DateExtra data2(data1);
	DateExtra data3 = data1;
	DateExtra data4("Linux", 2, 4.2f);
	int nD = 0;
	DateExtra* vectorDateExtra = new DateExtra[nD];
	DateExtra::adaugaDateInVector(vectorDateExtra, data0, nD);
	DateExtra::adaugaDateInVector(vectorDateExtra, data1, nD);
	DateExtra::adaugaDateInVector(vectorDateExtra, data2, nD);
	DateExtra::adaugaDateInVector(vectorDateExtra, data3, nD);
	DateExtra::adaugaDateInVector(vectorDateExtra, data4, nD);
	cout << "Introduceti numele fisierului sesiuni.txt!\n";
	char* numeFisier;
	char buffer[50]; // joaca rol de buffer
	cin.getline(buffer, 50);
	numeFisier = new char[strlen(buffer) + 1];
	strcpy_s(numeFisier, strlen(buffer) + 1, buffer);
	if (strcmp(numeFisier, "sesiuni.txt") != 0) {
		int ok = 0;
		while (ok == 0)
		{
			cout << "Nu ati introdus numele corespunzator! Numele corect este sesiuni.txt!\n";
			char buffer[50];
			cin.getline(buffer, 50);
			numeFisier = new char[strlen(buffer) + 1];
			strcpy_s(numeFisier, strlen(buffer) + 1, buffer);
			if (strcmp(numeFisier, "sesiuni.txt") == 0)
				ok = 1;
		}
	}
	ifstream fisier(numeFisier, ios::in);
	int nC = 0;
	ProfilBaza* vectorProfilBaseCitit = new ProfilBaza[nC];
	while (true)
	{
		ProfilBaza profCitit;
		fisier >> profCitit;
		ProfilBaza::adaugaProfilInVector(vectorProfilBaseCitit, profCitit, nC);
		if (fisier.eof())
			break;
	}
	system("cls");
	int **matriceCoincid;
	matriceCoincid = new int*[nC];
	for (int i = 0; i < nC; i++)
		matriceCoincid[i] = new int[nB];
	for (int i = 0; i < nC; i++)
		for (int j = 0; j < nB; j++)
			matriceCoincid[i][j] = 0;
	int ok;
	for (int i = 0; i < nB; i++) {
		for (int j = 0; j < nC; j++)
		{
			ok = 1;
			if (abs(vectorProfilBaseCitit[j].getStg() - vectorProfilBase[i].getStg() > 5))
				ok = 0;
			if (abs(vectorProfilBaseCitit[j].getDr() - vectorProfilBase[i].getDr() > 5))
				ok = 0;
			if (abs(vectorProfilBaseCitit[j].getNrTasteApasate() - vectorProfilBase[i].getNrTasteApasate() > 15))
				ok = 0;
			if (ok == 1)
				matriceCoincid[j][i] = i;
		}
	}
	int pref;
	do {
		Meniu();
		cout << "Introduceti un numar de la 1 la 8:\n";
		cin >> pref;
		system("cls");
		if (pref == 1)
		{
			cout << "\tProfilele de baza de pana acum sunt:\n";
			for (int i = 0; i < nB; i++)
				cout << vectorProfilBase[i];
			cout << "\tProfile coincidente:\n";
			cout << endl;
			for (int i = 0; i < nC; i++)
				for (int j = 0; j < nB; j++)
					if (matriceCoincid[i][j])
						cout << "Profilul citit " << i + 1 << " coincide cu profilul existent " << j << endl;
			cout << endl;
			cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
			int altaOper, val = 0;
			cin >> altaOper;
			if (altaOper < 1 || altaOper>2) {
				do {
					cout << "\nNu ati introdus o valoare corespunzatoare! Introduceti din nou, fie valoarea 1, fie valoarea 2. ";
					cin >> altaOper;
					if (altaOper >= 1 && altaOper <= 2)
						val = 1;
				} while (val == 0);
			}
			if (altaOper == 1)
			{
				system("cls");
			}
			else {
				break;
			}
		}
		if (pref == 2)
		{
			ProfilBaza profInt;
			cin >> profInt;
			ProfilBaza::adaugaProfilInVector(vectorProfilBase, profInt, nB);
			ProfilAdv profNec;
			ProfilAdv::adaugaProfilAdvInVector(vectorProfilAdv, profNec, nA);
			DateExtra dateNec;
			DateExtra::adaugaDateInVector(vectorDateExtra, dateNec, nD);
			matriceCoincid = new int* [nC];
			for (int i = 0; i < nC; i++)
				matriceCoincid[i] = new int[nB];
			for (int i = 0; i < nC; i++)
				for (int j = 0; j < nB; j++)
					matriceCoincid[i][j] = 0;
			int ok;
			for (int i = 0; i < nB; i++) {
				for (int j = 0; j < nC; j++)
				{
					ok = 1;
					if (abs(vectorProfilBaseCitit[j].getStg() - vectorProfilBase[i].getStg() > 5))
						ok = 0;
					if (abs(vectorProfilBaseCitit[j].getDr() - vectorProfilBase[i].getDr() > 5))
						ok = 0;
					if (abs(vectorProfilBaseCitit[j].getNrTasteApasate() - vectorProfilBase[i].getNrTasteApasate() > 15))
						ok = 0;
					if (ok == 1)
						matriceCoincid[j][i] = i;
				}
			}
			cout << "\tProfile coincidente:\n";
			cout << endl;
			for (int i = 0; i < nC; i++)
				for (int j = 0; j < nB; j++)
					if (matriceCoincid[i][j])
						cout << "Profilul citit " << i + 1 << " coincide cu profilul existent " << j << endl;
			cout << endl;
			cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
			int altaOper, val = 0;
			cin >> altaOper;
			if (altaOper < 1 || altaOper>2) {
				do {
					cout << "\nNu ati introdus o valoare corespunzatoare! Introduceti din nou, fie valoarea 1, fie valoarea 2. ";
					cin >> altaOper;
					if (altaOper >= 1 && altaOper <= 2)
						val = 1;
				} while (val == 0);
			}
			if (altaOper == 1)
			{
				system("cls");
			}
			else {
				break;
			}
		}
		if (pref == 3)
		{
			cout << "Introduceti un nr de la 1 la " << nB - 1 << " pentru profilul dorit!\n";
			int i;
			cin >> i;
			if (i < 1 || i >(nB - 1)) {
				int ok = 0;
				while (ok == 0)
				{
					cout << "Nu ati introdus o valoare corespunzatoare!Introduceti un nr de la 1 la " << nB - 1 << " pentru profilul dorit!\n";
					cin >> i;
					if (i >= 1 && i <= nB - 1)
						ok = 1;
				}
			}
			cout << vectorProfilAdv[i] << endl;
			cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
			int altaOper, val = 0;
			cin >> altaOper;
			if (altaOper < 1 || altaOper>2) {
				do {
					cout << "\nNu ati introdus o valoare corespunzatoare! Introduceti din nou, fie valoarea 1, fie valoarea 2. ";
					cin >> altaOper;
					if (altaOper >= 1 && altaOper <= 2)
						val = 1;
				} while (val == 0);
			}
			if (altaOper == 1)
			{
				system("cls");
			}
			else {
				break;
			}
		}
		if (pref == 4) {
			cout << "Introduceti un nr de la 1 la " << nB - 1 << " pentru profilul dorit!\n";
			int i;
			cin >> i;
			if (i < 1 || i >(nB - 1)) {
				int ok = 0;
				while (ok == 0)
				{
					cout << "Nu ati introdus o valoare corespunzatoare!Introduceti un nr de la 1 la " << nB - 1 << " pentru profilul dorit!\n";
					cin >> i;
					if (i >= 1 && i <= nB - 1)
						ok = 1;
				}
			}
			cin.get();
			cout << "Modul de copiere: ";
			char bufferLucru[50];
			char* modLucru;
			cin.getline(bufferLucru, 50);
			modLucru = new char[strlen(bufferLucru) + 1];
			strcpy_s(modLucru, strlen(bufferLucru) + 1, bufferLucru);
			if ((strcmp(modLucru, "meniu") != 0) && (strcmp(modLucru, "scurtaturi") != 0) && (strcmp(modLucru, "mix") != 0)) {
				int ok = 0;
				while (ok == 0)
				{
					cout << "Nu ati introdus un mod de lucru corespunzator! Modurile de lucru corecte sunt 'meniu', 'scurtaturi', 'mix'!\n";
					cin.getline(bufferLucru, 50);
					modLucru = new char[strlen(bufferLucru) + 1];
					strcpy_s(modLucru, strlen(bufferLucru) + 1, bufferLucru);
					if (strcmp(modLucru, "meniu") == 0 || strcmp(modLucru, "scurtaturi") == 0 || strcmp(modLucru, "mix") == 0)
						ok = 1;
				}
			}
			cout << '\n';
			cout << "Introduceti ratia profilului: ";
			int ratie;
			cin >> ratie;
			Detalii<int>det1(vectorProfilBase[i].getStg(), modLucru, ratie);
			Detalii<int>det2(vectorProfilBase[i].getDr(), modLucru, ratie);
			cout << "Diferenta intre click-uri pentru profilul " << i << "= " << det1 - det2 << endl;
			cout << endl;
			cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
			int altaOper, val = 0;
			cin >> altaOper;
			if (altaOper < 1 || altaOper>2) {
				do {
					cout << "\nNu ati introdus o valoare corespunzatoare! Introduceti din nou, fie valoarea 1, fie valoarea 2. ";
					cin >> altaOper;
					if (altaOper >= 1 && altaOper <= 2)
						val = 1;
				} while (val == 0);
			}
			if (altaOper == 1){
				system("cls");
			}
			else {
				break;
			}
		}
		if (pref == 5) {
			cout << "Introduceti un nr de la 1 la " << nB - 1 << " pentru profilul dorit!\n";
			int i;
			cin >> i;
			if (i < 1 || i > (nB - 1)) {
				int ok = 0;
				while (ok == 0)
				{
					cout << "Nu ati introdus o valoare corespunzatoare!Introduceti un nr de la 1 la " << nB - 1 << " pentru profilul dorit!\n";
					cin >> i;
					if (i >= 1 && i <= nB - 1)
						ok = 1;
				}
			}
			cout << "\tGETTER PROFIL BAZA\n";
			cout << "Nr.clickuri stanga profil " << i << "= " << vectorProfilBase[i].getStg() << endl;
			cout << "Nr.clickuri dreapta profil " << i << "= " << vectorProfilBase[i].getDr() << endl;
			cout << "Zona mouse profil " << i << ": ";
			switch (vectorProfilBase[i].getZona()) {
			case 1:
				cout << "Stanga sus\n";
				break;
			case 2:
				cout << "Stanga jos\n";
				break;
			case 3:
				cout << "Dreapta sus\n";
				break;
			case 4:
				cout << "Dreapta jos\n";
				break;
			case 5:
				cout << "Centru\n";
				break;
			default:
				cout << "nu are zona cursor, este neinitializat\n";
				break;
			}
			cout << "Numar taste apasate= " << vectorProfilBase[i].getNrTasteApasate() << endl;
			cout << "Adresa IP profil: " << vectorProfilBase[i].getAdresaIP() << endl;
			cout << "Nr Accesari profil= " << vectorProfilBase[i].getNrAccesari() << endl;
			cout << "\tGETTER PROFIL AVANSAT\n";
			cout << "Status verificare email (1->verificat/0->neverificat): " << vectorProfilAdv[i].getVerifEmail() << endl;
			cout << "Adresa de e-mail: " << vectorProfilAdv[i].getEmail() << '\n';
			cout << "Numarul de apasari a tastei Shift= " << vectorProfilAdv[i].getNrShift() << endl;
			cout << "\tGETTER DATE EXTRA\n";
			cout << "Sistemul de operare profil " << i << ": " << vectorDateExtra[i].getSistemOperare() << endl;
			cout << "Vechime profil " << i << "=  " << vectorDateExtra[i].getVechime() << endl;
			cout << "Ratie profil " << i << "= " << vectorDateExtra[i].getRatie() << endl;
			cout << endl;
			cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
			int altaOper, val = 0;
			cin >> altaOper;
			if (altaOper < 1 || altaOper>2) {
				do {
					cout << "\nNu ati introdus o valoare corespunzatoare! Introduceti din nou, fie valoarea 1, fie valoarea 2. ";
					cin >> altaOper;
					if (altaOper >= 1 && altaOper <= 2)
						val = 1;
				} while (val == 0);
			}
			if (altaOper == 1){
				system("cls");
			}
			else {
				break;
			}
		}
		if (pref == 6) {
			ScriereCSV** afis;
			afis = new ScriereCSV * [1];
			cout << "Introduceti un nr de la 1 la " << nA - 1 << " pentru profilul dorit!\n";
			int i;
			cin >> i;
			if (i < 1 || i >(nA - 1)) {
				int ok = 0;
				while (ok == 0)
				{
					cout << "Nu ati introdus o valoare corespunzatoare!Introduceti un nr de la 1 la " << nA - 1 << " pentru profilul dorit!\n";
					cin >> i;
					if (i >= 1 && i <= nA - 1)
						ok = 1;
				}
			}
			afis[0] = &vectorProfilBase[i];
			cin.get();
			cout << "Introduceti numele fisierului in care doriti sa salvati profilul: ";
			char bufferB[50];
			char* numeFis;
			cin.getline(buffer, 50);
			numeFis = new char[strlen(bufferB) + 1];
			strcpy_s(numeFis, strlen(bufferB) + 1, bufferB);
			ofstream g(numeFis, ios::app);
			afis[0]->scrieInFisier(g);
			g.close();
			delete[] afis;
			cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
			int altaOper, val = 0;
			cin >> altaOper;
			if (altaOper < 1 || altaOper>2) {
				do {
					cout << "\nNu ati introdus o valoare corespunzatoare! Introduceti din nou, fie valoarea 1, fie valoarea 2. ";
					cin >> altaOper;
					if (altaOper >= 1 && altaOper <= 2)
						val = 1;
				} while (val == 0);
			}
			if (altaOper == 1){
				system("cls");
			}
			else {
				break;
			}
		}
		if (pref == 7) {
			ScriereCSV** afis;
			afis = new ScriereCSV * [2];
			cout << "Introduceti un nr de la 1 la " << nA - 1 << " pentru profilul dorit!\n";
			int i;
			cin >> i;
			if (i < 1 || i >(nA - 1)) {
				int ok = 0;
				while (ok == 0)
				{
					cout << "Nu ati introdus o valoare corespunzatoare!Introduceti un nr de la 1 la " << nA - 1 << " pentru profilul dorit!\n";
					cin >> i;
					if (i >= 1 && i <= nA - 1)
						ok = 1;
				}
			}
			cin.get();
			cout << "Introduceti numele fisierului in care doriti sa salvati profilul: ";
			char bufferA[50];
			char* numeFis;
			cin.getline(buffer, 50);
			numeFis = new char[strlen(bufferA) + 1];
			strcpy_s(numeFis, strlen(bufferA) + 1, bufferA);
			afis[0] = &vectorProfilAdv[i];
			afis[1] = &vectorDateExtra[i];
			ofstream g(numeFis, ios::app);
			for (int i = 0; i < 2; i++) {
				afis[i]->scrieInFisier(g);
			}
			g.close();
			delete[] afis;
			cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
			int altaOper, val = 0;
			cin >> altaOper;
			if (altaOper < 1 || altaOper>2) {
				do {
					cout << "\nNu ati introdus o valoare corespunzatoare! Introduceti din nou, fie valoarea 1, fie valoarea 2. ";
					cin >> altaOper;
					if (altaOper >= 1 && altaOper <= 2)
						val = 1;
				} while (val == 0);
			}
			if (altaOper == 1){
				system("cls");
			}
			else {
				break;
			}
		}
		if (pref == 8) {
			ProfilAdv profInt;
			cin >> profInt;
			DateExtra dateInt;
			cin >> dateInt;
			ProfilAdv::adaugaProfilAdvInVector(vectorProfilAdv, profInt, nA);
			ProfilBaza::adaugaProfilInVector(vectorProfilBase, (ProfilBaza)profInt, nB);
			DateExtra::adaugaDateInVector(vectorDateExtra, dateInt, nD);
			matriceCoincid = new int* [nC];
			for (int i = 0; i < nC; i++)
				matriceCoincid[i] = new int[nB];
			for (int i = 0; i < nC; i++)
				for (int j = 0; j < nB; j++)
					matriceCoincid[i][j] = 0;
			int ok;
			for (int i = 0; i < nB; i++) {
				for (int j = 0; j < nC; j++)
				{
					ok = 1;
					if (abs(vectorProfilBaseCitit[j].getStg() - vectorProfilBase[i].getStg() > 5))
						ok = 0;
					if (abs(vectorProfilBaseCitit[j].getDr() - vectorProfilBase[i].getDr() > 5))
						ok = 0;
					if (abs(vectorProfilBaseCitit[j].getNrTasteApasate() - vectorProfilBase[i].getNrTasteApasate() > 15))
						ok = 0;
					if (ok == 1)
						matriceCoincid[j][i] = i;
				}
			}
			cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
			int altaOper, val = 0;
			cin >> altaOper;
			if (altaOper < 1 || altaOper>2) {
				do {
					cout << "\nNu ati introdus o valoare corespunzatoare! Introduceti din nou, fie valoarea 1, fie valoarea 2. ";
					cin >> altaOper;
					if (altaOper >= 1 && altaOper <= 2)
						val = 1;
				} while (val == 0);
			}
			if (altaOper == 1){
				system("cls");
			}
			else {
				break;
			}
		}
	} while (pref > 0 && pref < 9);
	if (vectorDateExtra != NULL)
		delete[] vectorDateExtra;
	if (vectorProfilBase != NULL)
		delete[] vectorProfilBase;
	if (vectorProfilAdv != NULL)
		delete[] vectorProfilAdv;
	for (int i = 0; i < nC; ++i)
		delete[] matriceCoincid[i];
	delete[] matriceCoincid;
}