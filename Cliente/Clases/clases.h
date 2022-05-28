#ifndef _CLASES_H_
#define _CLASES_H_

namespace clases {

    class Cartera {
    private:
        int ID_Cartera;
        float saldo;
        int ID_Usuario;
    public:
        Cartera(int idCartera, float saldo, int idUsuario);
        Cartera(const Cartera& c);
        void imprimirCartera();
    };

    class Transaccion {
    private:
        int ID_Transaccion;
        float Cantidad;
        int Fecha;
        int ID_Objeto;
        int ID_Cartera_Recibe;
        int ID_Cartera_Envia;
    public:
        // Constructores y destructores
        Transaccion(int idTrans, float cantidad, int fecha, int idObjeto, int idCartEnvia, int idCartRec);
        Transaccion(const Transaccion& t);

        // Getters y Setters
        int getIDTrans();
        float getCant();
        int getFecha();
        int getIDObjeto();
        int getIDCarteraRecibe();
        int getIDCarteraEnvia();

        void setIDTrans(int id);
        void setCant(int cant);
        void setFecha(int fecha);
        void setIDObjeto(int idObjeto);
        void setIDCarteraRecibe(int idCartera);
        void setIDCarteraEnvia(int idCartera);

        // Metodos
        void imprimirTransaccion();
    };

    class Objeto {
    private:
        int ID_Objeto;
        char* Categoria;
        char* Estado;
        char* Descripcion;
        float PrecioSalida;
        int ID_Subastador;
        int ID_Lote;
    public:
        // Constructores y destructores
        Objeto();
        Objeto(int idObjeto, char* cat, char* estado, char* desc, float precioSal, int idSubastador, int idLote);
        Objeto(const Objeto& o);
        ~Objeto();
        // Getters y Setters
 
        int getIDObjeto();
        char* getCategoria();
        char* getEstado();
        char* getDescripcion();
        float getPrecioSalida();
        int getIDSubastador();
        int getID_Lote();

        void setIDObjeto(int id);
        void setCategoria(char* categoria);
        void setEstado(char* estado);
        void setDescripcion(char* descripcion);
        void setPrecioSalida(float precio);
        void setIDSubastador(int id);
        void setIDLote(int id);

        // Metodos
        void imprimirObjeto();
    };

    class Lote {
    private:
        int idLote;
        int fechaCom;
        int fechaFin;
        char* estado;
        int avgPrecio; // del 1 al 4 dependiendo del precio medio [$, $$, $$$, $$$$]
        int cantidadObjetos;
        Objeto* listaObjetos;
    public:
        // Constructores y destructores
        Lote(int idLote, int fechaCom, int fechaFin, char* estado, int avgPrecio, int cantObj, Objeto* listaObjetos);
        Lote(const Lote& l);
        ~Lote();
        // Getters y Setters

        int getIDLote();
        int getFechaCom();
        int getFechaFin();
        char* getEstado();
        int getAvgPrecio();
        int getCantidadObjetos();
        Objeto* getListaObjetos();

        void setIDLote(int id);
        void setFechaCom(int fecha);
        void setFechaFin(int fecha);
        void setEstado(char* estado);
        // setAvgPrecio no tiene sentido, se tiene que calcular en el constructor y al a�adir/eliminar objetos
        void setCantidadObjetos(int cant);
        void setListaObjetos(Objeto* listaObjetos, int cantidadObjetos);

        // Metodos
        void anadirObjeto(Objeto& o);
        void calcularAvgPrecio();
        void eliminarObjeto(int idObjeto);
        void imprimirLote();
    };

    class Usuario {
        private:
            int ID_Usuario;
            char* Contrasenia;
            char* Nombre;
            int Tlf;
            char* Mail;
            int Puntos;
            int ID_Cartera;
            char* Pais;
            char* Ciudad;
            char* Calle;
            char* PisoPuerta;
        public:
            // Constructores y destructores
            Usuario(int idUsuario, char* contra, char* nombre, int tlf, char* mail, int puntos, int idCartera, char* pais, char* ciudad, char* calle, char* pisoPuerta);
            Usuario(const Usuario& u);
            Usuario();
            ~Usuario();
            // Getters y Setters

            static int idUsing;
            int getIDUsuario();
            char* getContrasenia();
            char* getNombre();
            int getTlf();
            char* getMail();
            int getPuntos();
            int getIDCartera();
            char* getPais();
            char* getCiudad();
            char* getCalle();
            char* getPisoPuerta();

            void setIDUsuario(int id);
            void setContrasenia(char* contrasenia);
            void setNombre(char* nombre);
            void setTlf(int tlf);
            void setMail(char* mail);
            void setPuntos(int puntos);
            void setIDCartera(int id);
            void setPais(char* pais);
            void setCiudad(char* ciudad);
            void setCalle(char* calle);
            void setPisoPuerta(char* pisoPuerta);

            // Metodos
            void imprimirUsuario();
            char* toString();
       
       
    };
}
#endif