#include "clases.h"
#include <iostream>
#include <string.h>

using namespace std;

namespace clases {


	Cartera::Cartera(int idCartera, float saldo, int idUsuario) {
		this->ID_Cartera = idCartera;
		this->ID_Usuario = idUsuario;
		this->saldo = saldo;
	}
	Cartera::Cartera(const Cartera& c) {
		this->ID_Cartera = c.ID_Cartera;
		this->ID_Usuario = c.ID_Usuario;
		this->saldo = c.saldo;
	}
	void Cartera::imprimirCartera() {
		cout << "----------[CARTERA]----------\n";
		cout << "ID_Cartera: " << this->ID_Cartera << endl;
		cout << "ID_Usuario: " << this->ID_Usuario << endl;
		cout << "Saldo: " << this->saldo << endl;
		cout << "--------[FIN-CARTERA]--------\n";
	}

	Transaccion::Transaccion(int idTrans, float cantidad, int fecha, int idObjeto, int idCartEnvia, int idCartRec) {
		this->ID_Transaccion = idTrans;
		this->Cantidad = cantidad;
		this->Fecha = fecha;
		this->ID_Objeto = idObjeto;
		this->ID_Cartera_Envia = idCartEnvia;
		this->ID_Cartera_Recibe = idCartRec;
	}
	Transaccion::Transaccion(const Transaccion& t) {
		this->ID_Transaccion = t.ID_Transaccion;
		this->Cantidad = t.Cantidad;
		this->Fecha = t.Fecha;
		this->ID_Objeto = t.ID_Objeto;
		this->ID_Cartera_Envia = t.ID_Cartera_Envia;
		this->ID_Cartera_Recibe = t.ID_Cartera_Recibe;
	}

	// Getters y Setters
	int Transaccion::getIDTrans() {
		return this->ID_Transaccion;
	}
	float Transaccion::getCant() {
		return this->Cantidad;
	}
	int Transaccion::getFecha() {
		return this->Fecha;
	}
	int Transaccion::getIDObjeto() {
		return this->ID_Objeto;
	}
	int Transaccion::getIDCarteraRecibe() {
		return this->ID_Cartera_Recibe;
	}
	int Transaccion::getIDCarteraEnvia() {
		return this->ID_Cartera_Envia;
	}

	void Transaccion::setIDTrans(int id) {
		this->ID_Transaccion = id;
	}
	void Transaccion::setCant(int cant) {
		this->Cantidad = cant;
	}
	void Transaccion::setFecha(int fecha) {
		this->Fecha = fecha;
	}
	void Transaccion::setIDObjeto(int idObjeto) {
		this->ID_Objeto = idObjeto;
	}
	void Transaccion::setIDCarteraRecibe(int idCartera) {
		this->ID_Cartera_Recibe = idCartera;
	}
	void Transaccion::setIDCarteraEnvia(int idCartera) {
		this->ID_Cartera_Envia = idCartera;
	}
	void Transaccion::imprimirTransaccion() {
		cout << "----------[TRANSACCION]----------\n";
		cout << "ID_Transaccion: " << this->ID_Transaccion << endl;
		cout << "Cantidad: " << this->Cantidad << endl;
		cout << "Fecha: " << this->Fecha << endl;
		cout << "ID_Objeto: " << this->ID_Objeto << endl;
		cout << "ID_Cartera_Envia: " << this->ID_Cartera_Envia << endl;
		cout << "ID_Cartera_Recibe: " << this->ID_Cartera_Recibe << endl;
		cout << "--------[FIN-TRANSACCION]--------\n";
	}

	// Constructores y destructores
	Objeto::Objeto() {

	}
	Objeto::Objeto(int idObjeto, char* cat, char* estado, char* desc, float precioSal, int idSubastador, int idLote) {
		this->ID_Objeto = idObjeto;
		this->Categoria = new char[strlen(cat) + 1];
		strcpy(this->Categoria, cat);
		this->Estado = new char[strlen(estado) + 1];
		strcpy(this->Estado, estado);
		this->Descripcion = new char[strlen(desc) + 1];
		strcpy(this->Descripcion, desc);
		this->PrecioSalida = precioSal;
		this->ID_Subastador = idSubastador;
		this->ID_Lote = idLote;
	}
	Objeto::Objeto(const Objeto& o) {
		this->ID_Objeto = o.ID_Objeto;
		this->Categoria = new char[strlen(o.Categoria) + 1];
		strcpy(this->Categoria, o.Categoria);
		this->Estado = new char[strlen(o.Estado) + 1];
		strcpy(this->Estado, o.Estado);
		this->Descripcion = new char[strlen(o.Descripcion) + 1];
		strcpy(this->Descripcion, o.Descripcion);
		this->PrecioSalida = o.PrecioSalida;
		this->ID_Subastador = o.ID_Subastador;
		this->ID_Lote = o.ID_Lote;
	}
	Objeto::~Objeto() {
		delete[] this->Categoria;
		delete[] this->Estado;
		delete[] this->Descripcion;
	}
	// Getters y Setters

	int Objeto::getIDObjeto() {
		return this->ID_Objeto;
	}
	char* Objeto::getCategoria() {
		return this->Categoria;
	}
	char* Objeto::getEstado() {
		return this->Estado;
	}
	char* Objeto::getDescripcion() {
		return this->Descripcion;
	}
	float Objeto::getPrecioSalida() {
		return this->PrecioSalida;
	}
	int Objeto::getIDSubastador() {
		return this->ID_Subastador;
	}
	int Objeto::getID_Lote() {
		return this->ID_Lote;
	}

	void Objeto::setIDObjeto(int id) {
		this->ID_Objeto = id;
	}
	void Objeto::setCategoria(char* categoria) {
		delete[] this->Categoria;
		this->Categoria = new char[strlen(categoria) + 1];
		strcpy(this->Categoria, categoria);

	}
	void Objeto::setEstado(char* estado) {
		delete[] this->Estado;
		this->Estado = new char[strlen(estado) + 1];
		strcpy(this->Estado, estado);
	}
	void Objeto::setDescripcion(char* descripcion) {
		delete[] this->Descripcion;
		this->Descripcion = new char[strlen(descripcion) + 1];
		strcpy(this->Descripcion, descripcion);
	}
	void Objeto::setPrecioSalida(float precio) {
		this->PrecioSalida = precio;
	}
	void Objeto::setIDSubastador(int id) {
		this->ID_Subastador = id;
	}
	void Objeto::setIDLote(int id) {
		this->ID_Lote = id;
	}

	// Metodos
	void Objeto::imprimirObjeto() {

		cout << "----------[OBJETO]----------\n";
		cout << "ID_Objeto: " << this->ID_Objeto << endl;
		cout << "Categoria: " << this->Categoria << endl;
		cout << "Estado: " << this->Estado << endl;
		cout << "Descripcion: " << this->Descripcion << endl;
		cout << "PrecioSalida: " << this->PrecioSalida << endl;
		cout << "ID_Subastador: " << this->ID_Subastador << endl;
		cout << "ID_Lote: " << this->ID_Lote << endl;
		cout << "--------[FIN-OBJETO]--------\n";

	}

	// Constructores y destructores
	Lote::Lote(int idLote, int fechaCom, int fechaFin, char* estado, int avgPrecio, int cantObj, Objeto* listaObjetos) {
		this->idLote = idLote;
		this->fechaCom = fechaCom;
		this->fechaFin = fechaFin;
		this->estado = new char[strlen(estado) + 1];
		strcpy(this->estado, estado);
		this->avgPrecio = avgPrecio;
		this->cantidadObjetos = cantObj;
		this->listaObjetos = new Objeto[cantObj];
		for (int i = 0; i < cantObj; i++) {
			this->listaObjetos[i] = listaObjetos[i];
		}
	}
	Lote::Lote(const Lote& l) {
		this->idLote = l.idLote;
		this->fechaCom = l.fechaCom;
		this->fechaFin = l.fechaFin;
		this->estado = new char[strlen(l.estado) + 1];
		strcpy(this->estado, l.estado);
		this->avgPrecio = l.avgPrecio;
		this->cantidadObjetos = l.cantidadObjetos;
		this->listaObjetos = new Objeto[l.cantidadObjetos];
		for (int i = 0; i < l.cantidadObjetos; i++) {
			this->listaObjetos[i] = l.listaObjetos[i];
		}
	}
	Lote::~Lote() {
		delete[] this->listaObjetos;
		delete[] this->estado;
	}
	// Getters y Setters

	int Lote::getIDLote() {
		return this->idLote;
	}
	int Lote::getFechaCom() {
		return this->fechaCom;
	}
	int Lote::getFechaFin() {
		return this->fechaFin;
	}
	char* Lote::getEstado() {
		return this->estado;
	}
	int Lote::getAvgPrecio() {
		return this->avgPrecio;
	}
	int Lote::getCantidadObjetos() {
		return this->cantidadObjetos;
	}
	Objeto* Lote::getListaObjetos() {
		return this->listaObjetos;
	}

	void Lote::setIDLote(int id) {
		this->idLote = id;
	}
	void Lote::setFechaCom(int fecha) {
		this->fechaCom = fecha;
	}
	void Lote::setFechaFin(int fecha) {
		this->fechaFin = fecha;
	}
	void Lote::setEstado(char* estado) {
		delete[] this->estado;
		this->estado = new char[strlen(estado) + 1];
		strcpy(this->estado, estado);
	}
	// setAvgPrecio no tiene sentido, se tiene que calcular en el constructor y al a�adir/eliminar objetos
	void Lote::setCantidadObjetos(int cant) {
		this->cantidadObjetos = cant;
	}
	void Lote::setListaObjetos(Objeto* listaObjetos, int cantidadObjetos) {
		delete[] this->listaObjetos;
		this->listaObjetos = new Objeto[cantidadObjetos];
		for (int i = 0; i < cantidadObjetos; i++) {
			this->listaObjetos[i] = listaObjetos[i];
		}
	}

	// Metodos
	void Lote::anadirObjeto(Objeto& o) {
		Objeto aux[this->cantidadObjetos];
		for (int i = 0; i < this->cantidadObjetos; i++) {
			aux[i] = this->listaObjetos[i];
		}

		this->cantidadObjetos++;

		delete[] this->listaObjetos;
		this->listaObjetos = new Objeto[this->cantidadObjetos];
		for (int i = 0; i < this->cantidadObjetos - 1; i++) {
			this->listaObjetos[i] = aux[i];
		}
		this->listaObjetos[this->cantidadObjetos - 1] = o;
		this->calcularAvgPrecio();
	}
	void Lote::calcularAvgPrecio() {
		int sumaTotal = 0;
		for (int i = 0; i < this->cantidadObjetos; i++) {
			sumaTotal += this->listaObjetos[i].getPrecioSalida();
		}
		this->avgPrecio = sumaTotal / this->cantidadObjetos;
	}
	void Lote::eliminarObjeto(int idObjeto) {
		// Tengo sue�o ns como hacerlo ahora mismo :C ZzZzZ
	}
	void Lote::imprimirLote() {
		cout << "----------[LOTE]----------\n";
		cout << "ID_Lote: " << this->idLote << endl;
		cout << "Fecha_Comienzo: " << this->fechaCom << endl;
		cout << "Fecha_Fin: " << this->fechaFin << endl;
		cout << "Estado: " << this->estado << endl;
		cout << "Avg_Precio: " << this->avgPrecio << endl;
		cout << "Cantidad_Objetos: " << this->cantidadObjetos << endl;
		cout << "ListaObjetos:\n";
		for (int i = 0; i < this->cantidadObjetos; i++) {
			listaObjetos[i].imprimirObjeto();
		}
		cout << "--------[FIN-LOTE]--------\n";
	}


	// Constructores y destructores
	int Usuario::idUsing;
}