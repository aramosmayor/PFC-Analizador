#pragma once

#include "Emerge2.h"
#include "macros.h"
#include <vcclr.h>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <exception>

#using <mscorlib.dll>

#define MAX_SUSPENSIVOS 5

namespace Analizador {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Data::OleDb;
	using namespace System::Data::Common;
	using namespace System::Runtime::InteropServices; 
	using namespace System::Text;
	using namespace System::Xml;
	using namespace System::Xml::XPath;


	bool forma_canonica, categoria, flexion, gen_num, art_pre, pronombre;
	std::vector< std::vector<int> > v_categorias;
	std::vector< std::vector<int> > v_flexiones;
	std::vector<int> v_pron_personal;

	//---------------------------------------------------------------------------
	//Estructura que guardará la información que nos interesa de los resultados
	//para posteriormente generar todas las combinaciones posibles para cada locución
	struct Info
	{
		char     FormaCanonica[MAX_LON];
		int      Categoria;    // Categoría gramatical.
		short	 Flexion;
		unsigned char GenNum;
		char	 Pronombre[MAX_LON];
		bool	 Clave;
	};

	//---------------------------------------------------------------------------
	//Sobrecarga del operador de igualdad para el struct Info
	bool operator==(Info x, Info y)
	{		
		bool result = false;

		result = forma_canonica ? strcmp(x.FormaCanonica, y.FormaCanonica) == 0 : result;
		if (result) result = categoria ? x.Categoria == y.Categoria : result;
		if (result) result = flexion ? x.Flexion == y.Flexion : result;
		if (result) result = gen_num ? x.GenNum == y.GenNum : result;
		if (result) result = pronombre ? strcmp(x.Pronombre, y.Pronombre) == 0 : result;

		return result;		
	}

	/// <summary>
	/// Resumen de Form1
	///
	/// ADVERTENCIA: si cambia el nombre de esta clase, deberá cambiar la
	///          propiedad 'Nombre de archivos de recursos' de la herramienta de compilación de recursos administrados
	///          asociada con todos los archivos .resx de los que depende esta clase. De lo contrario,
	///          los diseñadores no podrán interactuar correctamente con los
	///          recursos adaptados asociados con este formulario.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:

		[DllImport("Emerge2.dll")] static void inicializaMorfo(const char* );
		[DllImport("Emerge2.dll")] static void reconoce(const char *Palabra, Resultado *Res, int &NumPalabras, unsigned char ConPrefijo );

		String ^ f_res_base;
		String ^ f_res_varela_base;
		String ^ f_res_base_art_pre;
		String ^ f_res_varela_base_art_pre;
		String ^ f_locs;
		String ^ f_locs_varela;
		String ^ f_ejemplos;
		String ^ f_no_rec;
		String ^ fich_path;
		String ^ f_categorias;
		String ^ f_flexiones;
		String ^ f_comparativa;
		String ^ f_comparativa_varela;

	private: System::Windows::Forms::TextBox^  Fichero_TB;
			 System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::CheckBox^  FLEX_CB;
	private: System::Windows::Forms::CheckBox^  CAT_CB;
	private: System::Windows::Forms::CheckBox^  GEN_NUM_CB;
	private: System::Windows::Forms::CheckBox^  FC_CB;
	private: System::Windows::Forms::CheckBox^  ART_PRE_CB;




	public: 

		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			f_res_base = "..\\Datos\\Out\\resultados.xml";
			f_res_varela_base = "..\\Datos\\Out\\resultados_varela.xml";
			f_res_base_art_pre = "..\\Datos\\Out\\resultados_art_pre.xml";
			f_res_varela_base_art_pre = "..\\Datos\\Out\\resultados_varela_art_pre.xml";
			f_locs = "..\\Datos\\Out\\locuciones.xml";	
			f_locs_varela = "..\\Datos\\Out\\locuciones_varela.xml";		
			f_no_rec = "..\\Datos\\Out\\no_reconocidas.txt";
			fich_path = "..\\Datos\\In\\Ficheros\\";		
			f_ejemplos = "ejemplos.txt";
			f_categorias = "..\\Datos\\In\\Categorias_gramaticales.txt";
			f_flexiones = "..\\Datos\\In\\Codigos_flexion_verbos.txt";
			f_comparativa = "..\\Datos\\Out\\comparativa_";	
			f_comparativa_varela = "..\\Datos\\Out\\comparativa_varela_";	
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén utilizando.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 

	private:
		/// <summary>
		/// Variable del diseñador requerida.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido del método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->Fichero_TB = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->FLEX_CB = (gcnew System::Windows::Forms::CheckBox());
			this->CAT_CB = (gcnew System::Windows::Forms::CheckBox());
			this->GEN_NUM_CB = (gcnew System::Windows::Forms::CheckBox());
			this->FC_CB = (gcnew System::Windows::Forms::CheckBox());
			this->ART_PRE_CB = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(329, 19);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Analizar";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// Fichero_TB
			// 
			this->Fichero_TB->Location = System::Drawing::Point(66, 21);
			this->Fichero_TB->Name = L"Fichero_TB";
			this->Fichero_TB->Size = System::Drawing::Size(229, 20);
			this->Fichero_TB->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(45, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Fichero:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->FLEX_CB);
			this->groupBox1->Controls->Add(this->CAT_CB);
			this->groupBox1->Controls->Add(this->GEN_NUM_CB);
			this->groupBox1->Controls->Add(this->FC_CB);
			this->groupBox1->Location = System::Drawing::Point(18, 71);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(386, 82);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			// 
			// FLEX_CB
			// 
			this->FLEX_CB->AutoSize = true;
			this->FLEX_CB->Location = System::Drawing::Point(27, 50);
			this->FLEX_CB->Name = L"FLEX_CB";
			this->FLEX_CB->Size = System::Drawing::Size(59, 17);
			this->FLEX_CB->TabIndex = 3;
			this->FLEX_CB->Text = L"Flexión";
			this->FLEX_CB->UseVisualStyleBackColor = true;
			// 
			// CAT_CB
			// 
			this->CAT_CB->AutoSize = true;
			this->CAT_CB->Checked = true;
			this->CAT_CB->CheckState = System::Windows::Forms::CheckState::Checked;
			this->CAT_CB->Enabled = false;
			this->CAT_CB->Location = System::Drawing::Point(228, 19);
			this->CAT_CB->Name = L"CAT_CB";
			this->CAT_CB->Size = System::Drawing::Size(73, 17);
			this->CAT_CB->TabIndex = 2;
			this->CAT_CB->Text = L"Categoría";
			this->CAT_CB->UseVisualStyleBackColor = true;
			// 
			// GEN_NUM_CB
			// 
			this->GEN_NUM_CB->AutoSize = true;
			this->GEN_NUM_CB->Location = System::Drawing::Point(228, 50);
			this->GEN_NUM_CB->Name = L"GEN_NUM_CB";
			this->GEN_NUM_CB->Size = System::Drawing::Size(109, 17);
			this->GEN_NUM_CB->TabIndex = 1;
			this->GEN_NUM_CB->Text = L"Género y Número";
			this->GEN_NUM_CB->UseVisualStyleBackColor = true;
			// 
			// FC_CB
			// 
			this->FC_CB->AutoSize = true;
			this->FC_CB->Checked = true;
			this->FC_CB->CheckState = System::Windows::Forms::CheckState::Checked;
			this->FC_CB->Enabled = false;
			this->FC_CB->Location = System::Drawing::Point(27, 19);
			this->FC_CB->Name = L"FC_CB";
			this->FC_CB->Size = System::Drawing::Size(103, 17);
			this->FC_CB->TabIndex = 0;
			this->FC_CB->Text = L"Forma Canónica";
			this->FC_CB->UseVisualStyleBackColor = true;
			// 
			// ART_PRE_CB
			// 
			this->ART_PRE_CB->AutoSize = true;
			this->ART_PRE_CB->Location = System::Drawing::Point(45, 181);
			this->ART_PRE_CB->Name = L"ART_PRE_CB";
			this->ART_PRE_CB->Size = System::Drawing::Size(190, 17);
			this->ART_PRE_CB->TabIndex = 4;
			this->ART_PRE_CB->Text = L"No incluir artículos y preposiciones";
			this->ART_PRE_CB->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(424, 211);
			this->Controls->Add(this->ART_PRE_CB);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Fichero_TB);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Analizador";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}


		//---------------------------------------------------------------------------
		//Función que devuelve una estructura de tipo Info a partir de una estructura Resultado
		Info CopiaAInfo(Resultado res, bool es_clave)
		{
			Info info;

			//Se copian los campos FormaCanonica, Categoria, Flexion y GenNum
			strcpy_s(info.FormaCanonica, res.FormaCanonica);
			info.Categoria = res.Categoria;
			info.Flexion = res.Flexion;
			info.GenNum = res.GenNum;
			info.Clave = es_clave;
			strcpy_s(info.Pronombre, res.Pronombre);

			return info;
		}


		//---------------------------------------------------------------------------
		//Función que, a partir de una ristra, devuelve una nueva ristra a la que se le
		//han quitado todos aquellos símbolos que no sean letras
		String ^ QuitaSimbolos(String ^ locucion)
		{
			String ^ linea;
			int indice = -1;

			while(locucion->Contains("\n"))
			{
				indice = locucion->IndexOf("\n");
				linea = "";
				if (indice > 0)
					linea = locucion->Substring(0, indice);
				if (indice < locucion->Length - 1)
					linea += " " + locucion->Substring(indice + 1);
				locucion = locucion->Copy(linea);
			}

			while(locucion->Contains("\r"))
			{
				indice = locucion->IndexOf("\r");
				linea = "";
				if (indice > 0)
					linea = locucion->Substring(0, indice);
				if (indice < locucion->Length - 1)
					linea += " " + locucion->Substring(indice + 1);
				locucion = locucion->Copy(linea);
			}

			while(locucion->Contains("<"))
			{
				indice = locucion->IndexOf("<");
				linea = "";
				if (indice > 0)
					linea = locucion->Substring(0, indice);
				if (indice < locucion->Length - 1)
					linea += " " + locucion->Substring(indice + 1);
				locucion = locucion->Copy(linea);
			}

			while(locucion->Contains(">"))
			{
				indice = locucion->IndexOf(">");
				linea = "";
				if (indice > 0)
					linea = locucion->Substring(0, indice);
				if (indice < locucion->Length - 1)
					linea += " " + locucion->Substring(indice + 1);
				locucion = locucion->Copy(linea);
			}

			//Elimina espacios iniciales si los hubiera
			while(locucion->IndexOf(" ") == 0)
				locucion = locucion->Substring(1);

			//Elimina espacios finales si los hubiera
			while(locucion->Length > 0 && locucion->LastIndexOf(" ") == locucion->Length - 1)
				locucion = locucion->Substring(0, locucion->Length - 1);

			//Elimina los dobles espacios
			while (locucion->Contains("  "))
			{
				indice = locucion->IndexOf("  ");
				linea = "";
				if (indice > 0)
					linea = locucion->Substring(0, indice);
				linea += " ";
				if (indice < locucion->Length - 2)
					linea += locucion->Substring(indice + 2);
				locucion = locucion->Copy(linea);
			}

			//Elimina los dobles espacios
			while (locucion->Contains("d'"))
			{
				indice = locucion->IndexOf("d'");
				linea = "";
				if (indice > 0)
					linea = locucion->Substring(0, indice);
				linea += "de ";
				if (indice < locucion->Length - 2)
					linea += locucion->Substring(indice + 2);
				locucion = locucion->Copy(linea);
			}

			return locucion;
		}

		bool EsPronombrePersonal(int categoria)
		{
			for(int i = 0; i < v_pron_personal.size(); i++)
			{
				if (v_pron_personal[i] == categoria)
					return true;
			}
			return false;
		}

		bool EsVerbo(std::vector<Info> Resultados)
		{
			for(int i = 0; i < Resultados.size(); i++)
			{
				for(int j = 0; j < v_categorias[8].size(); j++)
				{
					if (Resultados[i].Categoria == v_categorias[8][j])
						return true;
				}
			}

			return false;
		}

		std::vector<char *> ObtienePronombres(char * pronombres)
		{
			int i = 0, lon = 0;
			char * trozo = new char[MAX_LON];
			std::vector<char *> lista_pronombres;
			unsigned char ConPrefijo = 3;

			while (i < strlen(pronombres))
			{
				trozo[lon++] = pronombres[i++];
				trozo[lon] = '\0';				

				Resultado Res[MAX_RES];
				int nRes = 0;
				reconoce(trozo, Res, nRes, ConPrefijo);

				for(int j = 0; j < nRes; j++)
				{
					if (EsPronombrePersonal(Res[j].Categoria))
					{
						char * pronombre = new char[MAX_LON];
						strcpy(pronombre, trozo);
						lista_pronombres.push_back(pronombre);
						lon = 0;
						break;
					}
				}
			}

			return lista_pronombres;
		}

		//--------------------------------------------------------------------
		//Procedimiento que, a partir de las locuciones leídas de la base de datos, obtiene todas
		//las locuciones posibles al interpretar los símbolos de las mismas, modificando la matriz
		//de caracteres que se le pasa. Ahí se guardará, para cada posición de la ristra, los posibles
		//valores (palabras) que lo ocuparán
		std::vector< std::vector<char *> > ObtieneLocucionesVarela(char * locucion)
		{
			std::vector< std::vector<char *> > locuciones;
			char * trozo = new char[MAX_LON_ORA];
			char * loc_aux = new char[MAX_LON_ORA];
			strcpy(trozo, "");

			int i = 0;
			while (i < strlen(locucion))
			{
				if (locucion[i] == '{') //quita el símbolo "{" y su correspondiente "}"
				{
					int contador = 1;
					int j = i + 1;
					while (j < strlen(locucion))
					{
						if (locucion[j] == '}')
							contador--;
						if (locucion[j] == '{')
							contador++;
						if (contador == 0)
							break;
						j++;
					}
					char * aux = strcpy(aux, locucion);
					locucion = strncpy(locucion, aux, i);
					if (contador == 0)
					{
						loc_aux = strncpy(loc_aux, aux + i + 1, j - i - 1);
						loc_aux[j-i-1] = '\0';
						strcat(locucion, loc_aux);
						loc_aux = strcpy(loc_aux, aux + j + 1);						
						strcat(locucion, loc_aux);
					}
					else
					{
						loc_aux = strcpy(loc_aux, aux + i + 1);			
						strcat(locucion, loc_aux);
					}
				}
				else
				{
					if (locucion[i] == '|')//quita el símbolo "|"
					{
						char * aux = strcpy(aux, locucion);
						locucion = strncpy(locucion, aux, i);
						locucion[i] = '\0';
						loc_aux = strcpy(loc_aux, aux + i + 1);		
						strcat(locucion, loc_aux);
					}
					else
					{
						if (locucion[i] == '(') //extrae toda la opción entre paréntesis de la locución y la trata, combinando el resultado con lo obtenido hasta el momento
						{
							if (strlen(trozo) > 0)
							{
								if (locuciones.size() == 0)
								{
									std::vector<char *> aux;
									locuciones.push_back(aux);
								}
								for(int j = 0; j < locuciones.size(); j++)
								{
									char * new_loc = new char[MAX_LON_ORA];
									strcpy(new_loc, trozo);
									locuciones[j].push_back(new_loc);
								}
								trozo = strcpy(trozo, "");
							}
							int contador = 1;
							int j = i + 1;
							while (j < strlen(locucion))
							{
								if (locucion[j] == ')')
									contador--;
								if (locucion[j] == '(')
									contador++;
								if (contador == 0)
									break;
								j++;
							}
							char * opcional = new char[MAX_LON_ORA];
							char * aux = new char[MAX_LON_ORA];
							strcpy(aux, locucion);
							if (contador == 0)
							{
								opcional = strncpy(opcional, locucion + i + 1, j - i - 1);
								opcional[j-i-1] = '\0';
							}
							else
								opcional = strcpy(opcional, locucion + i + 1);
							locucion = strncpy(locucion, aux, i);
							locucion[i] = '\0';
							if (contador == 0)
								locucion = strcpy(locucion, aux + j + 1);
							else
								strcpy(locucion, "");
							i = 0;
							std::vector< std::vector<char *> > opciones = ObtieneLocucionesVarela(opcional);
							//se añade opción vacía al final
							std::vector<char *> vacio;
							vacio.push_back("");
							opciones.push_back(vacio);
							if (locuciones.size() == 0)
								locuciones = opciones;
							else
							{
								int tam = locuciones.size();
								for (int k = 0; k < tam; k++)
								{
									for(int l = 0; l < opciones.size(); l++)
									{
										std::vector<char *> vlocucion = locuciones[0];
										for(int m = 0; m < opciones[l].size(); m++)
											vlocucion.push_back(opciones[l][m]);
										locuciones.push_back(vlocucion);
									}
									locuciones.erase(locuciones.begin());
								}
							}
						}
						else
						{
							if (locucion[i] == '/')
							{
								if (strlen(trozo) > 0)
								{
									char * trozo_aux = new char[MAX_LON_ORA];
									strcpy(trozo_aux, trozo);
									std::vector<char *> aux;
									aux.push_back(trozo_aux);
									locuciones.push_back(aux);
									strcpy(trozo, "");
									if (i < strlen(locucion) - 1)
										locucion = strcpy(locucion, locucion + i + 1);
									else
										strcpy(locucion, "");
									i = 0;
								}
								int interno = 0;
								while(i < strlen(locucion))
								{
									if (locucion[i] == '/' && interno == 0)
									{
										char * trozo_aux = new char[MAX_LON_ORA];
										strcpy(trozo_aux, trozo);

										std::vector< std::vector<char *> > aux = ObtieneLocucionesVarela(trozo_aux);
										if (aux.size() > 0)
										{
											if (locuciones.size() == 0)
												locuciones = aux;
											else
											{
												for (int k = 0; k < aux.size(); k++)
													locuciones.push_back(aux[k]);
											}
										}
										strcpy(trozo, "");
									}
									else
									{
										if (locucion[i] == '(' || locucion[i] == '[' || locucion[i] == '<')
											interno++;
										if (locucion[i] == ')' || locucion[i] == ']' || locucion[i] == '>')
											interno--;
										char * aux = new char[2];
										strncpy(aux, locucion + i, 1);
										aux[1] = '\0';
										strcat(trozo, aux);
									}
									i++;
								}
								if (i < strlen(locucion) - 1)
									locucion = strcpy(locucion, locucion + i + 1);
								else
									strcpy(locucion, "");
								i = 0;
								if (strlen(trozo) > 0)
								{
									char * trozo_aux = new char[MAX_LON_ORA];
									strcpy(trozo_aux, trozo);
									std::vector< std::vector<char *> > aux = ObtieneLocucionesVarela(trozo_aux);
									if (aux.size() > 0)
									{
										if (locuciones.size() == 0)
											locuciones = aux;
										else
										{
											for (int k = 0; k < aux.size(); k++)
												locuciones.push_back(aux[k]);
										}
									}
									strcpy(trozo, "");
								}
							}
							else
							{
								if (locucion[i] == '[')
								{
									if (strlen(trozo) > 0)
									{
										if (locuciones.size() == 0)
										{
											std::vector<char *> aux;
											locuciones.push_back(aux);
										}
										for(int j = 0; j < locuciones.size(); j++)
										{
											char * new_loc = new char[MAX_LON_ORA];
											strcpy(new_loc, trozo);
											locuciones[j].push_back(new_loc);
										}
										strcpy(trozo, "");
									}
									int contador = 1;
									int j = i + 1;
									while (j < strlen(locucion))
									{
										if (locucion[j] == ']')
											contador--;
										if (locucion[j] == '[')
											contador++;
										if (contador == 0)
											break;
										j++;
									}
									char * opcional = new char[MAX_LON_ORA];
									char * aux = new char[MAX_LON_ORA];
									strcpy(aux, locucion);
									if (contador == 0)
									{
										opcional = strncpy(opcional, locucion + i + 1, j - i - 1);
										opcional[j-i-1] = '\0';
									}
									else
										opcional = strcpy(opcional, locucion + i + 1);
									locucion = strncpy(locucion, aux, i);
									locucion[i] = '\0';
									if (contador == 0)
										locucion = strcpy(locucion, aux + j + 1);
									else 
										strcpy(locucion, "");
									i = 0;
									std::vector< std::vector<char *> > opciones = ObtieneLocucionesVarela(opcional);
									if (opciones.size() > 0)
									{
										if (locuciones.size() == 0)
											locuciones = opciones;
										else
										{
											int tam = locuciones.size();
											for (int k = 0; k < tam; k++)
											{
												for(int l = 0; l < opciones.size(); l++)
												{
													std::vector<char *> locucion = locuciones[0];
													for(int m = 0; m < opciones[l].size(); m++)
														locucion.push_back(opciones[l][m]);
													locuciones.push_back(locucion);
												}
												locuciones.erase(locuciones.begin());
											}
										}
									}
								}
								else
								{
									if (locucion[i] == '<')
									{
										if (strlen(trozo) > 0)
										{
											if (locuciones.size() == 0)
											{
												std::vector<char *> aux;
												locuciones.push_back(aux);
											}
											for(int j = 0; j < locuciones.size(); j++)
											{
												char * new_loc = new char[MAX_LON_ORA];
												strcpy(new_loc, trozo);
												locuciones[j].push_back(new_loc);
											}
											strcpy(trozo, "");
										}
										int contador = 1;
										int j = i + 1;
										while (j < strlen(locucion))
										{
											if (locucion[j] == '>')
												contador--;
											if (locucion[j] == '<')
												contador++;
											if (contador == 0)
												break;
											j++;
										}
										char * opcional = new char[MAX_LON_ORA];
										char * aux = new char[MAX_LON_ORA];
										strcpy(aux, locucion);
										if (contador == 0){
											opcional = strncpy(opcional, locucion + i + 1, j - i - 1);
											opcional[j-i-1] = '\0';
										}
										else
											opcional = strcpy(opcional, locucion + i + 1);
										if (contador == 0)
											locucion = strcpy(locucion, aux + j + 1);
										else 
											strcpy(locucion, "");
										i = 0;
										std::vector< std::vector<char *> > opciones = ObtieneLocucionesVarela(opcional);
										if (locuciones.size() == 0)
											locuciones = opciones;
										else
										{
											int tam = locuciones.size();
											for (int k = 0; k < tam; k++)
											{
												for(int l = 0; l < opciones.size(); l++)
												{
													std::vector<char *> vlocucion = locuciones[0];
													for(int m = 0; m < opciones[l].size(); m++)
														vlocucion.push_back(opciones[l][m]);
													locuciones.push_back(vlocucion);
												}
												locuciones.erase(locuciones.begin());
											}
										}
									}
									else
									{
										char * aux = new char[2];
										strncpy(aux, locucion + i, 1);
										aux[1] = '\0';
										strcat(trozo, aux);
										i++;
									}
								}
							}
						}
					}
				}
			}

			if (strlen(trozo) > 0)
			{
				if (locuciones.size() == 0)
				{
					std::vector<char *> aux;
					locuciones.push_back(aux);
				}
				for(int j = 0; j < locuciones.size(); j++)
				{
					char * new_loc = new char[MAX_LON_ORA];
					strcpy(new_loc, trozo);
					locuciones[j].push_back(new_loc);
				}
			}

			return locuciones;
		}


		//--------------------------------------------------------------------
		//Procedimiento que, a partir de las locuciones leídas de la base de datos, obtiene todas
		//las locuciones posibles al interpretar los símbolos de las mismas, modificando la matriz
		//de caracteres que se le pasa. Ahí se guardará, para cada posición de la ristra, los posibles
		//valores (palabras) que lo ocuparán
		std::vector< std::vector<char*> > ObtieneLocuciones( char * locucion, int &n_palabras, int n_opciones[MAX_PAL])
		{
			char * elemento;
			String ^ linea = gcnew String(locucion);
			char elementos[MAX_PAL][MAX_LON_PAL];
			int n_elementos = 0;
			std::vector< std::vector<char*> > loc_tratada;
			std::vector< std::vector<char*> > locuciones;

			locucion = (char*)(void*)Marshal::StringToHGlobalAnsi(QuitaSimbolos(linea));

			//Si existen llaves las quito porque lo único que significa es que se puede flexionar lo que está entre llaves
			//En "linea" se va copiando la locución de entrada, ya sin llaves
			if (strstr(locucion, "{") != NULL)
			{
				linea = "";
				elemento = strtok(locucion, "{}");
				while(elemento != NULL)
				{
					linea += gcnew String(elemento);
					elemento = strtok(NULL, "{}");
				}
				//volvemos a cargar la locucion limpia en "locucion"
				locucion = (char*)(void*)Marshal::StringToHGlobalAnsi(linea);
			}

			//Si existe "|"... no sé qué hacer, así que lo quito
			//En "linea" se va copiando la locución de entrada, ya sin "|"
			if (strstr(locucion, "|") != NULL)
			{
				linea = "";
				elemento = strtok(locucion, "|");
				while(elemento != NULL)
				{
					linea += gcnew String(elemento) + " ";
					elemento = strtok(NULL, "|");
				}          
				//volvemos a cargar la locucion limpia en "locucion"
				locucion = (char*)(void*)Marshal::StringToHGlobalAnsi(linea);
			}

			//Ahora se separa la linea por espacios
			elemento = strtok(locucion, " ");
			while(elemento != NULL)
			{
				strcpy(elementos[n_elementos++], elemento);
				elemento = strtok(NULL, " ");
			}

			for (int i = 0; i < n_elementos; i++)
			{
				n_opciones[n_palabras] = 0;
				char *inicio, *fin;

				//()          RISTRA NO VERBAL
				if (strstr(elementos[i], "(") != NULL)
				{
					inicio = strtok(elementos[i], "(");
					if (inicio != NULL)
					{
						if (loc_tratada.size() == n_palabras)
						{
							std::vector<char *> nueva_linea;
							loc_tratada.push_back(nueva_linea);
						}
						loc_tratada[n_palabras].push_back(" ");
						n_opciones[n_palabras]++;
						int parentesis = 0;
						while((strstr(/*inicio*/elementos[i], ")") == NULL || parentesis > 0) && i < n_elementos)
						{
							if (strstr(elementos[i], ")")) parentesis--;
							i++;
							inicio = strcat(inicio, " ");
							inicio = strcat(inicio, elementos[i]);
							if (strstr(elementos[i], "(")) 
								parentesis++;
						}
						int posicion = strlen(inicio) - 1;

						strcpy(elementos[i], "");
						strncpy(elementos[i], inicio, posicion);
						elementos[i][posicion] = '\0';
						fin = elementos[i];

						//hasta aquí chachi... ahora tengo que mirar si hay barras
						if (strstr(fin, "/") != NULL)
						{
							inicio = strtok(fin, "/");
							while (inicio != NULL)
							{
								if (loc_tratada.size() == n_palabras)
								{
									std::vector<char *> nueva_linea;
									loc_tratada.push_back(nueva_linea);
								}
								//una vez aquí, ya se han separado las distintas opciones y habrá que volver a comprobar si alguna tiene "()"
								if (strstr(inicio, "(") != NULL)
								{
									int n_pal = 0;
									int n_ops[MAX_PAL];
									std::vector< std::vector<char*> > opciones = ObtieneLocuciones(inicio, n_pal, n_ops);
									for (int j = 0; j < opciones.size(); j++)
									{
										String ^ opcion = "";
										for(int k = 0; k < opciones[j].size(); k++)
										{
											String ^ palabra = gcnew String(opciones[j][k]);
											opcion += " " + palabra;
										}
										opcion = QuitaSimbolos(opcion);
										if (loc_tratada.size() == n_palabras)
										{
											std::vector<char *> nueva_linea;
											loc_tratada.push_back(nueva_linea);
										}
										loc_tratada[n_palabras].push_back(((char*)(void*)Marshal::StringToHGlobalAnsi(opcion)));
										n_opciones[n_palabras]++;
									}
								}
								else
								{										
									loc_tratada[n_palabras].push_back(inicio);
									n_opciones[n_palabras]++;
								}
								inicio = strtok(NULL, "/");
							}
						}
						else
						{
							if (loc_tratada.size() == n_palabras)
							{
								std::vector<char *> nueva_linea;
								loc_tratada.push_back(nueva_linea);
							}
							loc_tratada[n_palabras].push_back(fin);
							n_opciones[n_palabras]++;
						}
					}
					else
						continue;
				}
				else
				{
					//<>     RISTRA VERBAL
					if (strstr(elementos[i], "<") != NULL)
					{
						inicio = strtok(elementos[i], "<");
						if (inicio != NULL)
						{
							while(strstr(inicio, ">") == NULL && i < n_elementos)
							{
								i++;
								inicio = strcat(inicio, " ");
								inicio = strcat(inicio, elementos[i]);
							}
							fin = strtok(inicio, ">");
							//se mira si hay barras
							if (strstr(fin, "/") != NULL)
							{
								inicio = strtok(fin, "/");
								while (inicio != NULL)
								{
									if (loc_tratada.size() == n_palabras)
									{
										std::vector<char *> nueva_linea;
										loc_tratada.push_back(nueva_linea);
									}
									loc_tratada[n_palabras].push_back(inicio);
									n_opciones[n_palabras]++;
									inicio = strtok(NULL, "/");
								}
							}
							else
							{
								if (loc_tratada.size() == n_palabras)
								{
									std::vector<char *> nueva_linea;
									loc_tratada.push_back(nueva_linea);
								}
								loc_tratada[n_palabras].push_back(fin);
								n_opciones[n_palabras]++;
							}
						}
						else
							continue;
					}
					else
					{
						if (strstr(elementos[i], "/") != NULL)
						{
							bool completa = false;

							if (elementos[i][strlen(elementos[i])-1] ==  '/')
								completa = true;

							inicio = strtok(elementos[i], "/");
							char * aux = strtok(NULL, "/");
							while (inicio != NULL)
							{
								if (aux == NULL && i != n_elementos - 1 && !completa)
								{
									while(strstr(inicio, "/") == NULL && i < n_elementos)
									{
										i++;
										inicio = strcat(inicio, " ");
										inicio = strcat(inicio, elementos[i]);
										if (elementos[i][strlen(elementos[i])-1] ==  '/')
											completa = true;
									}
									fin = strtok(inicio, "/");
									inicio = strtok(NULL, "/");
									aux = strtok(NULL, "/");
									//una vez aquí, ya se han separado las distintas opciones y habrá que volver a comprobar si alguna tiene "()"
									if (strstr(fin, "(") != NULL)
									{
										int n_pal = 0;
										int n_ops[MAX_PAL];
										std::vector< std::vector<char*> > opciones = ObtieneLocuciones(fin, n_pal, n_ops);
										for (int j = 0; j < opciones.size(); j++)
										{
											String ^ opcion = "";
											for(int k = 0; k < opciones[j].size(); k++)
											{
												String ^ palabra = gcnew String(opciones[j][k]);
												opcion += " " + palabra;
											}
											opcion = QuitaSimbolos(opcion);
											if (loc_tratada.size() == n_palabras)
											{
												std::vector<char *> nueva_linea;
												loc_tratada.push_back(nueva_linea);
											}
											loc_tratada[n_palabras].push_back(((char*)(void*)Marshal::StringToHGlobalAnsi(opcion)));
											n_opciones[n_palabras]++;
										}
									}
									else
									{
										if (loc_tratada.size() == n_palabras)
										{
											std::vector<char *> nueva_linea;
											loc_tratada.push_back(nueva_linea);
										}
										loc_tratada[n_palabras].push_back(fin);
										n_opciones[n_palabras]++;
									}
								}
								else
								{
									if (loc_tratada.size() == n_palabras)
									{
										std::vector<char *> nueva_linea;
										loc_tratada.push_back(nueva_linea);
									}
									char * item = new char(MAX_LON_PAL);
									strcpy(item, inicio);
									loc_tratada[n_palabras].push_back(item);
									n_opciones[n_palabras]++;
									if (aux != NULL)
										strcpy(inicio, aux);
									else
										inicio = NULL;
									aux = strtok(NULL, "/");
								}
							}
						}
						else
						{
							if (loc_tratada.size() == n_palabras)
							{
								std::vector<char *> nueva_linea;
								loc_tratada.push_back(nueva_linea);
							}
							loc_tratada[n_palabras].push_back(elementos[i]);
							n_opciones[n_palabras]++;
						}
					}
				}
				n_palabras++;
			}

			for(int j = 0; j < n_palabras; j++)
			{
				if (n_opciones[j] > 0)
					CombinaPalabras(loc_tratada[j], locuciones, n_opciones[j]);
			}
			return locuciones;
		}



		//---------------------------------------------------------------------------
		//Procedimiento que, dado un vector de palabras y un vector de ristras, obtiene todas las combinaciones
		//posibles de los mismos, modificando el vector de ristras.
		void CombinaPalabras(std::vector<char*> columna, std::vector< std::vector<char*> > &inicial, int numElem)
		{
			// preguntamos si el vector de vectores está vacío
			// entonces la "combinación" inicial es la que viene en columna.
			if(inicial.size() == 0)
			{
				for(int i = 0; i < numElem; i++)
				{
					std::vector<char*> v_comb;
					v_comb.push_back(columna[i]);
					inicial.push_back(v_comb);
				}
			}
			else    // si no está vacío
			{
				// recorremos el vector de vectores crearemos vectores con la
				// combinación del contenido de "inicial" y "columna" y lo
				// guardaremos en "inicial", una vez guardadas eliminaremos
				// las N ('indice_anterior', en este caso) combinaciones primeras.
				int indice_anterior = inicial.size();
				for(int i = 0; i< indice_anterior; i++)
				{
					for(int j = 0;j < numElem; j++)
					{
						std::vector<char*> pareja = inicial[0];

						pareja.push_back(columna[j]);
						inicial.push_back(pareja);
					}
					inicial.erase(inicial.begin());
				}
			}
		}


		//---------------------------------------------------------------------------
		//Procedimiento que, dado un vector de palabras y un vector de ristras, obtiene todas las combinaciones
		//posibles de los mismos, modificando el vector de ristras.
		std::vector< std::vector<int> > CombinaPosiciones(std::vector<int> columna, std::vector< std::vector<int> > &inicial, bool puntos_suspensivos)
		{
			// preguntamos si el vector de vectores está vacío
			// entonces la "combinación" inicial es la que viene en columna.
			if(inicial.size() == 0)
			{
				for(int i = 0; i < columna.size(); i++)
				{
					std::vector<int> v_comb;
					v_comb.push_back(columna[i]);
					inicial.push_back(v_comb);
				}

				return inicial;
			}
			else    // si no está vacío
			{
				std::vector< std::vector<int> > nuevo;
				// recorremos el vector de vectores crearemos vectores con la
				// combinación del contenido de "inicial" y "columna" y lo
				// guardaremos en "inicial", una vez guardadas eliminaremos
				// las N ('indice_anterior', en este caso) combinaciones primeras.
				for(int i = 0; i < inicial.size(); i++)
				{
					for(int j = 0;j < columna.size(); j++)
					{
						if (((columna[j] == inicial[i][inicial[i].size() - 1] + 1 && !puntos_suspensivos)
							|| (columna[j] <= (inicial[i][inicial[i].size() - 1] + MAX_SUSPENSIVOS + 1) && puntos_suspensivos))					
							&& columna[j] > inicial[i][inicial[i].size() - 1])
						{
							std::vector<int> pareja = inicial[i];

							pareja.push_back(columna[j]);
							nuevo.push_back(pareja);
						}
					}
				}

				return nuevo;
			}
		}

		//---------------------------------------------------------------------------
		//Procedimiento que, dado un vector de palabras y un vector de ristras, obtiene todas las combinaciones
		//posibles de los mismos, modificando el vector de ristras.
		/*void ObtieneSecuenciasConsecutivas(std::vector<int> columna, std::vector< std::vector<int> > &inicial)
		{
		// preguntamos si el vector de vectores está vacío
		// entonces la "combinación" inicial es la que viene en columna.
		if(inicial.size() == 0)
		{
		for(int i = 0; i < columna.size(); i++)
		{
		std::vector<int> v_comb;
		v_comb.push_back(columna[i]);
		inicial.push_back(v_comb);
		}
		}
		else    // si no está vacío
		{
		// recorremos el vector de vectores crearemos vectores con la
		// combinación del contenido de "inicial" y "columna" y lo
		// guardaremos en "inicial", una vez guardadas eliminaremos
		// las N ('indice_anterior', en este caso) combinaciones primeras.
		int indice_anterior = inicial.size();
		for(int i = 0; i< indice_anterior; i++)
		{
		for(int j = 0;j < columna.size(); j++)
		{
		std::vector<int> pareja = inicial[0];

		int ultimo = inicial[0][inicial[0].size()-1];

		if (columna[j] > ultimo)
		{
		for(int k = ultimo + 1; k <= columna[j]; k++)
		pareja.push_back(k);
		}

		inicial.push_back(pareja);
		}
		inicial.erase(inicial.begin());
		}
		}
		}*/

		//---------------------------------------------------------------------------
		//Función que comprueba que los valores de un struct Resultado ya estén incluidos
		//en un vector de struct Info
		bool EstaRes(Resultado res, std::vector<Info> lista)
		{
			struct Info elemento;

			elemento = CopiaAInfo(res, false);

			return EstaInfo(elemento, lista);
		}

		//---------------------------------------------------------------------------
		//Función que comprueba que los valores de un struct Resultado ya estén incluidos
		//en un vector de struct Info
		bool EstaTexto(char * texto, std::vector<char *> lista)
		{
			for(int i = 0; i < lista.size(); i++)
				if(strcmp(texto, lista[i]) == 0)
					return true;

			return false;
		}

		//---------------------------------------------------------------------------
		//Función que comprueba que los valores de un struct Resultado ya estén incluidos
		//en un vector de struct Info
		bool EstaInfo(Info res, std::vector<Info> lista)
		{
			for(int i = 0; i < lista.size(); i++)
				if(res == lista[i])
					return true;

			return false;
		}

		//---------------------------------------------------------------------------
		//Función que comprueba que los valores de un struct Resultado ya estén incluidos
		//en un vector de struct Info
		bool EstaInt(int elem, std::vector<int> lista)
		{
			for(int i = 0; i < lista.size(); i++)
			{
				if(elem == lista[i])
					return true;
			}

			return false;
		}

		//---------------------------------------------------------------------------
		//Procedimiento que devuelve en combinaciones todas las posibles combinaciones de
		//los resultados obtenidos al analizar cada palabra
		std::vector< std::vector< Info > > AnalizaPalabras(char * linea, std::vector< std::vector< Info > > Elementos, String ^ clave, std::vector<char*> * palabras_validas, std::vector<char*> * palabras_pronombre)
		{
			unsigned char ConPrefijo = 3;
			bool variante = false;
			std::vector<char*> palabras;
			char * palabra;
			int numpal = 0;
			palabras_validas->clear();
			palabras_pronombre->clear();

			palabra = strtok(linea, " ");

			while(palabra != NULL)
			{
				palabras.push_back(palabra);
				numpal++;
				palabra = strtok(NULL, " ");
			}

			Resultado Res_clave[MAX_RES];
			int nRes_clave = 0;
			reconoce((char*)(void*)Marshal::StringToHGlobalAnsi(clave), Res_clave, nRes_clave, ConPrefijo);

			//se analizan las palabras
			int palabras_con_resultado = 0;
			bool verbo_pronominal = false;
			std::vector<char *> lista_pronombres;

			for (int j = 0; j<numpal; j++)
			{
				bool up_uc = false;
				Resultado Res[MAX_RES];
				int nRes = 0;
				if (strstr(palabras[j], "ADJETIVO") == NULL &&
					strstr(palabras[j], "ADVERBIO") == NULL &&
					strstr(palabras[j], "ARTÍCULO") == NULL && 
					strstr(palabras[j], "NOMBRE_PROPIO") == NULL &&
					strstr(palabras[j], "NUMERAL") == NULL &&
					strstr(palabras[j], "PREPOSICIÓN") == NULL &&
					strstr(palabras[j], "PRONOMBRE") == NULL &&
					strstr(palabras[j], "SUSTANTIVO") == NULL &&
					strstr(palabras[j], "VERBO") == NULL &&
					strstr(palabras[j], "INFINITIVO") == NULL &&
					strstr(palabras[j], "INDICATIVO") == NULL &&
					strstr(palabras[j], "IMPERATIVO") == NULL &&
					strstr(palabras[j], "PARTICIPIO") == NULL &&
					strstr(palabras[j], "SUBJUNTIVO") == NULL &&
					strstr(palabras[j], "IMP_SUBJUNTIVO") == NULL)
					reconoce(palabras[j], Res, nRes, ConPrefijo);
				else
				{
					if (strstr(palabras[j], "ADJETIVO") != NULL)
					{
						nRes = v_categorias[0].size();
						for(int i = 0; i < v_categorias[0].size(); i++)
						{
							Res[i].FormaCanonica = new char(MAX_LON);
							strcpy(Res[i].FormaCanonica, "");
							Res[i].Pronombre = new char(MAX_LON);
							strcpy(Res[i].Pronombre, "");
							Res[i].Flexion = 0;
							Res[i].GenNum = 0;
							Res[i].Categoria = v_categorias[0][i];
						}
					}
					if (strstr(palabras[j], "ADVERBIO") != NULL)
					{
						nRes = v_categorias[1].size();
						for(int i = 0; i < v_categorias[1].size(); i++)
						{
							Res[i].FormaCanonica = new char(MAX_LON);
							strcpy(Res[i].FormaCanonica, "");
							Res[i].Pronombre = new char(MAX_LON);
							strcpy(Res[i].Pronombre, "");
							Res[i].Flexion = 0;
							Res[i].GenNum = 0;
							Res[i].Categoria = v_categorias[1][i];
						}
					}
					if (strstr(palabras[j], "ARTÍCULO") != NULL)
					{
						nRes = v_categorias[2].size();
						for(int i = 0; i < v_categorias[2].size(); i++)
						{
							Res[i].FormaCanonica = new char(MAX_LON);
							strcpy(Res[i].FormaCanonica, "");
							Res[i].Pronombre = new char(MAX_LON);
							strcpy(Res[i].Pronombre, "");
							Res[i].Flexion = 0;
							Res[i].GenNum = 0;
							Res[i].Categoria = v_categorias[2][i];
						}
					}
					if (strstr(palabras[j], "NOMBRE_PROPIO") != NULL)
					{
						nRes = v_categorias[3].size();
						for(int i = 0; i < v_categorias[3].size(); i++)
						{
							Res[i].FormaCanonica = new char(MAX_LON);
							strcpy(Res[i].FormaCanonica, "");
							Res[i].Pronombre = new char(MAX_LON);
							strcpy(Res[i].Pronombre, "");
							Res[i].Flexion = 0;
							Res[i].GenNum = 0;
							Res[i].Categoria = v_categorias[3][i];
						}
					}					
					if (strstr(palabras[j], "NUMERAL") != NULL)
					{
						nRes = v_categorias[4].size();
						for(int i = 0; i < v_categorias[4].size(); i++)
						{
							Res[i].FormaCanonica = new char(MAX_LON);
							strcpy(Res[i].FormaCanonica, "");
							Res[i].Pronombre = new char(MAX_LON);
							strcpy(Res[i].Pronombre, "");
							Res[i].Flexion = 0;
							Res[i].GenNum = 0;
							Res[i].Categoria = v_categorias[4][i];
						}
					}
					if (strstr(palabras[j], "PREPOSICIÓN") != NULL)
					{
						nRes = v_categorias[5].size();
						for(int i = 0; i < v_categorias[5].size(); i++)
						{
							Res[i].FormaCanonica = new char(MAX_LON);
							strcpy(Res[i].FormaCanonica, "");
							Res[i].Pronombre = new char(MAX_LON);
							strcpy(Res[i].Pronombre, "");
							Res[i].Flexion = 0;
							Res[i].GenNum = 0;
							Res[i].Categoria = v_categorias[5][i];
						}
					}
					if (strstr(palabras[j], "PRONOMBRE") != NULL)
					{
						nRes = v_categorias[6].size();
						for(int i = 0; i < v_categorias[6].size(); i++)
						{
							Res[i].FormaCanonica = new char(MAX_LON);
							strcpy(Res[i].FormaCanonica, "");
							Res[i].Pronombre = new char(MAX_LON);
							strcpy(Res[i].Pronombre, "");
							Res[i].Flexion = 0;
							Res[i].GenNum = 0;
							Res[i].Categoria = v_categorias[6][i];
						}
					}
					if (strstr(palabras[j], "SUSTANTIVO") != NULL)
					{
						nRes = v_categorias[7].size();
						for(int i = 0; i < v_categorias[7].size(); i++)
						{
							Res[i].FormaCanonica = new char(MAX_LON);
							strcpy(Res[i].FormaCanonica, "");
							Res[i].Pronombre = new char(MAX_LON);
							strcpy(Res[i].Pronombre, "");
							Res[i].Flexion = 0;
							Res[i].GenNum = 0;
							Res[i].Categoria = v_categorias[7][i];
						}
					}
					if (strstr(palabras[j], "VERBO") != NULL
						|| strstr(palabras[j], "INFINITIVO") != NULL)
					{
						nRes = v_categorias[8].size();
						for(int i = 0; i < v_categorias[8].size(); i++)
						{
							Res[i].FormaCanonica = new char(MAX_LON);
							strcpy(Res[i].FormaCanonica, "");
							Res[i].Pronombre = new char(MAX_LON);
							strcpy(Res[i].Pronombre, "");
							Res[i].Flexion = 0;
							Res[i].GenNum = 0;
							Res[i].Categoria = v_categorias[8][i];
						}
					}
					if (strstr(palabras[j], "INDICATIVO") != NULL)
					{
						nRes = 0;
						for(int i = 0; i < v_categorias[8].size(); i++)
						{
							for(int k = 0; k < v_flexiones[0].size(); k++)
							{
								Res[nRes].FormaCanonica = new char(MAX_LON);
								strcpy(Res[nRes].FormaCanonica, "");
								Res[nRes].Pronombre = new char(MAX_LON);
								strcpy(Res[nRes].Pronombre, "");
								Res[nRes].Flexion = v_flexiones[0][k];
								Res[nRes].GenNum = 0;
								Res[nRes].Categoria = v_categorias[8][i];
								nRes++;
							}
						}
					}
					if (strstr(palabras[j], "IMPERATIVO") != NULL)
					{
						nRes = 0;
						for(int i = 0; i < v_categorias[8].size(); i++)
						{
							for(int k = 0; k < v_flexiones[1].size(); k++)
							{
								Res[nRes].FormaCanonica = new char(MAX_LON);
								strcpy(Res[nRes].FormaCanonica, "");
								Res[nRes].Pronombre = new char(MAX_LON);
								strcpy(Res[nRes].Pronombre, "");
								Res[nRes].Flexion = v_flexiones[1][k];
								Res[nRes].GenNum = 0;
								Res[nRes].Categoria = v_categorias[8][i];
								nRes++;
							}
						}
					}
					if (strstr(palabras[j], "PARTICIPIO") != NULL)
					{
						nRes = 0;
						for(int i = 0; i < v_categorias[8].size(); i++)
						{
							for(int k = 0; k < v_flexiones[2].size(); k++)
							{
								Res[nRes].FormaCanonica = new char(MAX_LON);
								strcpy(Res[nRes].FormaCanonica, "");
								Res[nRes].Pronombre = new char(MAX_LON);
								strcpy(Res[nRes].Pronombre, "");
								Res[nRes].Flexion = v_flexiones[2][k];
								Res[nRes].GenNum = 0;
								Res[nRes].Categoria = v_categorias[8][i];
								nRes++;
							}
						}
					}
					if (strstr(palabras[j], "SUBJUNTIVO") != NULL)
					{
						nRes = 0;
						for(int i = 0; i < v_categorias[8].size(); i++)
						{
							for(int k = 0; k < v_flexiones[3].size(); k++)
							{
								Res[nRes].FormaCanonica = new char(MAX_LON);
								strcpy(Res[nRes].FormaCanonica, "");
								Res[nRes].Pronombre = new char(MAX_LON);
								strcpy(Res[nRes].Pronombre, "");
								Res[nRes].Flexion = v_flexiones[3][k];
								Res[nRes].GenNum = 0;
								Res[nRes].Categoria = v_categorias[8][i];
								nRes++;
							}
						}
					}
					if (strstr(palabras[j], "IMP_SUBJUNTIVO") != NULL)
					{
						nRes = 0;
						for(int i = 0; i < v_categorias[8].size(); i++)
						{
							for(int k = 0; k < v_flexiones[4].size(); k++)
							{
								Res[nRes].FormaCanonica = new char(MAX_LON);
								strcpy(Res[nRes].FormaCanonica, "");
								Res[nRes].Pronombre = new char(MAX_LON);
								strcpy(Res[nRes].Pronombre, "");
								Res[nRes].Flexion = v_flexiones[4][k];
								Res[nRes].GenNum = 0;
								Res[nRes].Categoria = v_categorias[8][i];
								nRes++;
							}
						}
					}
				}

				bool es_clave = false;

				for(int i = 0; i < nRes_clave; i++)
				{
					for(int j = 0; j < nRes; j++)
					{
						if (strcmp(Res_clave[i].FormaCanonica, Res[j].FormaCanonica) == 0)
						{
							es_clave = true;
							break;
						}
					}
					if (es_clave)
						break;
				}
				if (strcmp(palabras[j], (char*)(void*)Marshal::StringToHGlobalAnsi(clave)) == 0) 
					es_clave = true;

				//PARCHE DE LA VIDA PARA CUANDO NO RECONOCE ALGUNA PALABRA
				//En la forma canónica de Res[0] guarda la palabra y pone la categoría a 0 para indicar que no ha sido reconocida
				if (nRes == 0)
				{
					if (strcmp(palabras[j], "u.p.") == 0 || strcmp(palabras[j], "u.c.") == 0)
					{
						if (j > 0 && Elementos.size() > 0)
						{
							if (EsVerbo(Elementos[Elementos.size() - 1]))
							{
								char * aux = new char(MAX_LON);
								strcpy(aux, palabras_pronombre->back());
								palabras_pronombre->pop_back();
								for(int k = 0; k < lista_pronombres.size(); k++)
									palabras_pronombre->pop_back();
								palabras_pronombre->push_back("...");
								for(int k = 0; k < lista_pronombres.size(); k++)
									palabras_pronombre->push_back(lista_pronombres[k]);
								palabras_pronombre->push_back(aux);
								up_uc = true;
							}
							else
							{
								if (j > 1 && Elementos.size() > 1 && EsVerbo(Elementos[Elementos.size() - 2]))
								{
									if (strcmp(palabras[j - 1], "a") == 0)
									{
										palabras_pronombre->pop_back();
										char * aux = new char(MAX_LON);
										strcpy(aux, palabras_pronombre->back());
										palabras_pronombre->pop_back();
										for(int k = 0; k < lista_pronombres.size(); k++)
											palabras_pronombre->pop_back();
										palabras_pronombre->push_back("PRONOMBRE");
										for(int k = 0; k < lista_pronombres.size(); k++)
											palabras_pronombre->push_back(lista_pronombres[k]);
										palabras_pronombre->push_back(aux);
										up_uc = true;
									}
									else
									{
										if (strcmp(palabras[j - 1], "...") == 0)
										{
											//palabras_pronombre->pop_back();
											char * aux = new char(MAX_LON);
											strcpy(aux, palabras_pronombre->back());
											palabras_pronombre->pop_back();
											for(int k = 0; k < lista_pronombres.size(); k++)
												palabras_pronombre->pop_back();
											palabras_pronombre->push_back("...");
											for(int k = 0; k < lista_pronombres.size(); k++)
												palabras_pronombre->push_back(lista_pronombres[k]);
											palabras_pronombre->push_back(aux);
											up_uc = true;
										}
									}
								}
								else
								{
									if (j > 2 && Elementos.size() > 2 && EsVerbo(Elementos[Elementos.size() - 3]))
									{
										if (strcmp(palabras[j - 1], "a") == 0)
										{
											palabras_pronombre->pop_back();
											char * aux = new char(MAX_LON);
											strcpy(aux, palabras_pronombre->back());
											palabras_pronombre->pop_back();
											for(int k = 0; k < lista_pronombres.size(); k++)
												palabras_pronombre->pop_back();
											palabras_pronombre->push_back("PRONOMBRE");
											for(int k = 0; k < lista_pronombres.size(); k++)
												palabras_pronombre->push_back(lista_pronombres[k]);
											palabras_pronombre->push_back(aux);
											up_uc = true;
										}
										else
										{
											if (strcmp(palabras[j - 1], "...") == 0)
											{
												//palabras_pronombre->pop_back();
												char * aux = new char(MAX_LON);
												strcpy(aux, palabras_pronombre->back());
												palabras_pronombre->pop_back();
												for(int k = 0; k < lista_pronombres.size(); k++)
													palabras_pronombre->pop_back();
												palabras_pronombre->push_back("...");
												for(int k = 0; k < lista_pronombres.size(); k++)
													palabras_pronombre->push_back(lista_pronombres[k]);
												palabras_pronombre->push_back(aux);
												up_uc = true;
											}
										}

									}
								}
							}
						}

						strcpy(palabras[j], "...");
					}


					nRes = 1;
					Res[0].FormaCanonica = new char(MAX_LON);
					strcpy(Res[0].FormaCanonica, palabras[j]);
					Res[0].Pronombre = new char(MAX_LON);
					strcpy(Res[0].Pronombre, "");
					Res[0].Categoria = 0;
					Res[0].Flexion = 0;
					Res[0].GenNum = 0;
				}

				//aquí hay que cambiar: si es un artículo o una preposición no se analiza :)
				//hay que buscar los códigos de los artículos y las preposiciones para
				//hacer la pregunta
				if (nRes > 0)
				{
					bool valida = false;

					if (!up_uc)
					{
						verbo_pronominal = false;
						lista_pronombres.clear();
					}

					for(int k = 0; k < nRes; k++)
					{
						if (art_pre)
						{
							bool articulo_preposicion = false;
							for(int i = 0; i < v_categorias[2].size(); i++)
							{
								if (v_categorias[2][i] == Res[k].Categoria)
								{
									articulo_preposicion = true;
									break;
								}
							}
							if (articulo_preposicion) 
								continue;

							for(int i = 0; i < v_categorias[5].size(); i++)
							{
								if (v_categorias[5][i] == Res[k].Categoria)
								{
									articulo_preposicion = true;
									break;
								}
							}
							if (articulo_preposicion) 
								continue;
						}

						if (!verbo_pronominal)
						{
							for(int i = 0; i < v_categorias[8].size(); i++)
							{
								if (v_categorias[8][i] == Res[k].Categoria
									&& strlen(Res[k].Pronombre) > 0)
								{
									verbo_pronominal = true;
									char * pronombres = new char(MAX_LON);
									strcpy(pronombres, Res[k].Pronombre);
									//se obtienen los pronombres
									//y se añaden a la lista de palabras de la locución con el verbo pronominal
									lista_pronombres = ObtienePronombres(pronombres);

									for(int j = 0; j < lista_pronombres.size(); j++)
										palabras_pronombre->push_back(lista_pronombres[j]);

									char * verbo = new char(MAX_LON);
									strcpy(verbo, Res[k].FormaCanonica);
									palabras_pronombre->push_back(verbo);
									break;
								}
							}
						}

						valida = true;
						if(Elementos.size() > palabras_con_resultado)
						{
							if (!EstaRes(Res[k], Elementos[palabras_con_resultado]))
							{
								std::vector< Info > lista = Elementos[palabras_con_resultado];
								Elementos.pop_back();
								lista.push_back(CopiaAInfo(Res[k], es_clave));

								Elementos.push_back(lista);
							}
						}
						else
						{
							std::vector< Info > lista;
							Info elemento_nuevo = CopiaAInfo(Res[k], es_clave);
							lista.push_back(elemento_nuevo);
							Elementos.push_back(lista);
						}
					}
					if (valida)
					{
						palabras_con_resultado++;
						char * nueva_palabra = new char(MAX_LON);
						strcpy(nueva_palabra, palabras[j]);
						palabras_validas->push_back(nueva_palabra);
						if (!verbo_pronominal && !up_uc)
							palabras_pronombre->push_back(nueva_palabra);
						else
							variante = true;
					}
				}
			}

			if (!variante)
				palabras_pronombre->clear();

			return Elementos;
		}

		//---------------------------------------------------------------------------
		//Procedimiento que lee todas las locuciones de la base de datos, obtiene todas las
		//combinaciones posibles de las mismas y las analiza, almacenando sus resultados
		//en el fichero "resultados.xml"
		void AnalizaLocuciones(FileStream ^ no_reconocidas)
		{
			/*FileStream ^ fd = File::Create(f_locs);

			String ^ espacio = " ";
			String ^ salto = "\n";
			Encoding ^ linea = Encoding::Default;

			OleDbConnection ^ connection = gcnew OleDbConnection();
			connection->ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=..\\Datos\\Base.mdb;Mode=Share Deny None;Extended Properties="";Jet OLEDB:System database="";Jet OLEDB:Registry Path="";Jet OLEDB:Database Password="";Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password="";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False"; 
			connection->Open();
			OleDbCommand ^ query = gcnew OleDbCommand("SELECT * FROM LOCUCIONES", connection);

			int n_locs = 0;

			int numero_locucion = 1;

			OleDbDataReader ^ reader = query->ExecuteReader();

			String ^ linea_fichero = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
			int len = linea_fichero->Length;

			fd->Write(linea->GetBytes(linea_fichero), 0, len);
			linea_fichero = "<locuciones>\n";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);

			while(reader->Read())
			{
			//Para cada locución leída de la base de datos, la escribe en el fichero locuciones.txt
			int id_locucion = Convert::ToInt32(reader["Id"]->ToString());
			String ^ clave = reader["CLAVE"]->ToString();
			String ^ locucion = reader["LOCUCION"]->ToString();
			int len = 0;
			int n_palabras = 0;
			int n_opciones[MAX_PAL];
			std::vector< std::vector<char*> > locuciones;

			linea_fichero = "\t<locucion clave = \"" + clave + "\">\n";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);

			//Se obtienen todas las locuciones posibles de la línea leída
			locuciones = ObtieneLocuciones((char*)(void*)Marshal::StringToHGlobalAnsi(locucion), n_palabras, n_opciones);

			linea_fichero = "\t\t<texto loc = \"" + QuitaSimbolos(locucion) + "\">\n ";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);	
			//Se escriben las nuevas locuciones obtenidas en el fichero "locuciones.txt"
			for(int j = 0; j < locuciones.size(); j++)
			{
			int opcion = j+1;
			linea_fichero = "\t\t\t<opcion numero = \"" + opcion.ToString() + "\"> ";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);
			for (int k = 0; k < locuciones[j].size(); k++)
			{		
			len = strlen(locuciones[j][k]);
			array<Byte>^ charArray = gcnew array<Byte>(len + 2);
			Marshal::Copy((IntPtr)locuciones[j][k],charArray, 0, len);
			if (strcmp(locuciones[j][k], " "))
			{
			fd->Write(charArray, 0, len);
			len = espacio->Length;
			fd->Write(linea->GetBytes(espacio), 0, len);
			}
			}

			linea_fichero = "</opcion>\n";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);
			n_locs++;
			}					
			linea_fichero = "\t\t</texto>\n";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);

			linea_fichero = "\t</locucion>\n";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);
			}

			linea_fichero = "</locuciones>\n";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);

			connection->Close();
			fd->Close();*/
			
			//Se abre el fichero "locuciones.xml" en modo lectura
			//StreamReader ^ f = gcnew StreamReader(f_locs, System::Text::Encoding::GetEncoding("ISO-8859-1"));
			//Se carga el fichero de resultados del texto a probar
			XmlDocument ^ xmldoc = gcnew XmlDocument();
			xmldoc->Load(f_locs);
			XmlNode ^ doc_elem = xmldoc->DocumentElement;
			String ^ doc_cond = "//opcion";
			XmlNodeList ^ locucionesList = doc_elem->SelectNodes(doc_cond);

			System::Collections::IEnumerator^ locucionesEnum = locucionesList->GetEnumerator();

			FileStream ^ f_xml;
			if (art_pre)
				f_xml = File::Create(f_res_base_art_pre);
			else
				f_xml = File::Create(f_res_base);


			String ^ linea_fichero = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
			int len = linea_fichero->Length;
			Encoding ^ linea = Encoding::Default;

			f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
			linea_fichero = "<resultado>\n";
			len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

			int i = 0;
			std::vector<Info> n_recs;

			//Para cada coincidencia encontrada
			while ( locucionesEnum->MoveNext() )
			{		
				XmlNode^ nodo = safe_cast<XmlNode^>(locucionesEnum->Current);

				String ^ locucion = nodo->InnerText;//f->ReadLine();		

				while (locucion->Length > 0)
				{ 
					std::vector< std::vector<Info> > Elementos;
					std::vector< std::vector<Info> > combinaciones;

					i++;

					String ^ item_clave = nodo->ParentNode->ParentNode->Attributes["clave"]->Value->ToString();
					String ^ id_original = nodo->ParentNode->Attributes["numero"]->Value->ToString();

					linea_fichero = "\t<locucion id_locucion = \"" + id_original + "\" id = \"" + i.ToString() +  "\" clave = \"" + item_clave + "\" texto = \"" + locucion + "\">\n";
					len = linea_fichero->Length;
					f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

					String ^ locucion_formateada = FormateaLocucion(locucion);
					//locucion_formateada = locucion_formateada->Replace("u.p.", "...");
					//locucion_formateada = locucion_formateada->Replace("u.c.", "...");
					//locucion_formateada = locucion_formateada->Replace(" algo ", " ... ");
					//locucion_formateada = locucion_formateada->Replace(" alguien ", " ... ");
					locucion_formateada = locucion_formateada->Replace(" algo ", " u.c. ");
					locucion_formateada = locucion_formateada->Replace(" alguien ", " u.p. ");

					//Se analizan las palabras de la locución de forma independiente
					std::vector<char*> palabras_validas;
					std::vector<char*> palabras_pronombres;
					Elementos = AnalizaPalabras((char*)(void*)Marshal::StringToHGlobalAnsi(locucion_formateada), Elementos, item_clave, &palabras_validas, &palabras_pronombres);					

					//y se escriben todas las combinaciones posibles de resultados
					//en el fichero a continuación

					int numero_palabra = 0;
					//Se realizan todas las combinaciones posibles de los análisis obtenidos con anterioridad
					for (int j = 0; j < Elementos.size(); j++)
					{
						if (Elementos[j].size() > 0)
						{
							String ^ es_clave;
							if (Elementos[j][0].Clave)
								es_clave = "true";
							else
								es_clave = "false";
							String ^ simbolo = gcnew String(Elementos[j][0].FormaCanonica);
							if (simbolo == "." || simbolo == "," || simbolo == ";" || 
								simbolo == "¡" || simbolo == "!" || simbolo == "¿" || simbolo == "?" || 
								simbolo == "+" || simbolo == "'" || simbolo == ":" || simbolo == "`" ||
								simbolo == "%" || simbolo == "=" || simbolo == "-" || simbolo == "*" ||
								simbolo == "«" || simbolo == "»" || simbolo == "(" || simbolo == ")" || 
								simbolo == "[" || simbolo == "]" || simbolo == "<" || simbolo == ">" || 
								simbolo == "u.p." || simbolo == "u.c." || simbolo == "algo" || 
								simbolo == "alguien")
								continue;
							numero_palabra++;
							String ^ palabra_actual = gcnew String(palabras_validas[j]);
							linea_fichero = "\t\t<palabra numero = \"" + numero_palabra.ToString() + "\" clave = \"" +  es_clave + "\" texto = \"" + palabra_actual + "\"> \n";
							len = linea_fichero->Length;
							f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

							for(int k = 0; k < Elementos[j].size(); k++)
							{
								//Si se trata de una palabra no reconocida la guardamos
								if (Elementos[j][k].Categoria == 0 && !EstaInfo(Elementos[j][k], n_recs))
								{
									n_recs.push_back(Elementos[j][k]);
									String ^ f_canonica = gcnew String(Elementos[j][k].FormaCanonica);									
									if (f_canonica != "." && f_canonica != "..." && f_canonica != "," && f_canonica != ";" && 
										f_canonica != "¡" && f_canonica != "!" && f_canonica != "¿" && f_canonica != "?" && 
										f_canonica != "+" && f_canonica != "'" && f_canonica != ":" && f_canonica != "`" &&
										f_canonica != "%" && f_canonica != "=" && f_canonica != "-" && f_canonica != "*" &&
										f_canonica != "u.p." && f_canonica != "u.c."&& 											
										f_canonica != "«" && f_canonica != "»" && f_canonica != "(" && f_canonica != ")" && 
										f_canonica != "[" && f_canonica != "]" && f_canonica != "<" && f_canonica != ">")
									{
										String ^ linea_nr = "\"" + f_canonica + "\" en locución " + i.ToString() + "\n";
										no_reconocidas->Write(linea->GetBytes(linea_nr), 0, linea_nr->Length);
									}
								}	
								else
								{
									if (EsPronombrePersonal(Elementos[j][k].Categoria))
										strcpy(Elementos[j][k].FormaCanonica, "");
								}

								int numero_analisis = k+1;
								linea_fichero = "\t\t\t<analisis numero = \"" + numero_analisis.ToString() + "\" ";
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

								len = strlen(Elementos[j][k].FormaCanonica);
								array<Byte>^ charArray = gcnew array<Byte>(len + 2);
								Marshal::Copy((IntPtr)Elementos[j][k].FormaCanonica,charArray, 0, len);

								//forma_canonica
								linea_fichero = "FC = \"";
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
								len = strlen(Elementos[j][k].FormaCanonica);
								f_xml->Write(charArray, 0, len);
								linea_fichero = "\" "; 
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

								//categoria
								linea_fichero = "CG = \"" + Elementos[j][k].Categoria.ToString();
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
								linea_fichero = "\" "; 
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

								//flexion
								linea_fichero = "FL = \"" + Elementos[j][k].Flexion.ToString();
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
								linea_fichero = "\" "; 
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

								//gen_num
								linea_fichero = "GN = \"" + Elementos[j][k].GenNum.ToString(); + "\"/>\n";
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
								linea_fichero = "\" "; 
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

								//pronombre
								linea_fichero = "PR = \"";
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
								len = strlen(Elementos[j][k].Pronombre);
								charArray = gcnew array<Byte>(len + 2);
								Marshal::Copy((IntPtr)Elementos[j][k].Pronombre,charArray, 0, len);
								f_xml->Write(charArray, 0, len);
								linea_fichero = "\" "; 
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

								linea_fichero = "/>\n"; 
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

							}	

							linea_fichero = "\t\t</palabra>\n";
							len = linea_fichero->Length;
							f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
						}
					}

					linea_fichero = "\t</locucion>\n";
					len = linea_fichero->Length;
					f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

					locucion = "";

					if (palabras_pronombres.size() > 0)
					{
						for(int i = 0; i < palabras_pronombres.size(); i++)
							locucion += gcnew String(palabras_pronombres[i]) + " ";
					}
				}
			}

			linea_fichero = "</resultado>\n";
			len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

			f_xml->Close();
		}

		String ^ FormateaLocucion(String ^ locucion)
		{
			String ^ nueva_locucion = "";

			int len = locucion->Length;

			for(int i = 0; i < len; )
			{
				if (locucion[i] == '.')
				{
					if (locucion->IndexOf("...") == i)
					{
						nueva_locucion += " ... ";
						String ^ aux = locucion;
						locucion = aux->Substring(0, i);
						locucion += "   ";
						locucion += aux->Substring(i + 3);
						i+= 3;
					}
					else
					{
						if (i > 0 && locucion->IndexOf("u. p.") == i - 1)
						{
							nueva_locucion += ".p.";
							String ^ aux = locucion;
							locucion = aux->Substring(0, i - 1);
							locucion += "     ";
							locucion += aux->Substring(i + 4);
							i+=4;
						}
						else
						{
							if (i > 0 && locucion->IndexOf("u. c.") == i - 1)
							{
								nueva_locucion += ".c.";
								String ^ aux = locucion;
								locucion = aux->Substring(0, i - 1);
								locucion += "     ";
								locucion += aux->Substring(i + 4);
								i+=4;
							}
							else
							{
								nueva_locucion += " . ";
								String ^ aux = locucion;
								locucion = aux->Substring(0, i);
								locucion += " ";
								locucion += aux->Substring(i + 1);
								i++;
							}
						}
					}
				}
				else
				{	
					if (locucion[i] == ',')
					{
						nueva_locucion += " , ";
						String ^ aux = locucion;
						locucion = aux->Substring(0, i);
						locucion += " ";
						locucion += aux->Substring(i + 1);
						i++;
					}
					else
					{
						if (locucion[i] == ';')
						{
							nueva_locucion += " ; ";
							String ^ aux = locucion;
							locucion = aux->Substring(0, i);
							locucion += " ";
							locucion += aux->Substring(i + 1);
							i++;
						}
						else
						{
							if (locucion->IndexOf("¡") == i)
							{
								nueva_locucion += " ¡ ";
								String ^ aux = locucion;
								locucion = aux->Substring(0, i);
								locucion += " ";
								locucion += aux->Substring(i + 1);
								i++;
							}
							else
							{
								if (locucion->IndexOf("!") == i)
								{
									nueva_locucion += " ! ";
									String ^ aux = locucion;
									locucion = aux->Substring(0, i);
									locucion += " ";
									locucion += aux->Substring(i + 1);
									i++;
								}
								else
								{
									if (locucion->IndexOf("¿") == i)
									{
										nueva_locucion += " ¿ ";
										String ^ aux = locucion;
										locucion = aux->Substring(0, i);
										locucion += " ";
										locucion += aux->Substring(i + 1);
										i++;
									}
									else
									{
										if (locucion->IndexOf("?") == i)
										{
											nueva_locucion += " ? ";
											String ^ aux = locucion;
											locucion = aux->Substring(0, i);
											locucion += " ";
											locucion += aux->Substring(i + 1);
											i++;
										}
										else
										{
											if (locucion->IndexOf("'") == i
												|| locucion[i] == '\'')
											{
												nueva_locucion += " ' ";
												String ^ aux = locucion;
												locucion = aux->Substring(0, i);
												locucion += " ";
												locucion += aux->Substring(i + 1);
												i++;
											}
											else
											{
												if (locucion->IndexOf(":") == i)
												{
													nueva_locucion += " : ";
													String ^ aux = locucion;
													locucion = aux->Substring(0, i);
													locucion += " ";
													locucion += aux->Substring(i + 1);
													i++;
												}
												else
												{
													if (locucion->IndexOf("%") == i)
													{
														nueva_locucion += " % ";
														String ^ aux = locucion;
														locucion = aux->Substring(0, i);
														locucion += " ";
														locucion += aux->Substring(i + 1);
														i++;
													}
													else
													{
														if (locucion->IndexOf("=") == i)
														{
															nueva_locucion += " = ";
															String ^ aux = locucion;
															locucion = aux->Substring(0, i);
															locucion += " ";
															locucion += aux->Substring(i + 1);
															i++;
														}
														else
														{
															if (locucion->IndexOf("`") == i)
															{
																nueva_locucion += " ` ";
																String ^ aux = locucion;
																locucion = aux->Substring(0, i);
																locucion += " ";
																locucion += aux->Substring(i + 1);
																i++;
															}
															else
															{
																if (locucion->IndexOf("*") == i)
																{
																	nueva_locucion += " * ";
																	String ^ aux = locucion;
																	locucion = aux->Substring(0, i);
																	locucion += " ";
																	locucion += aux->Substring(i + 1);
																	i++;
																}
																else
																{
																	if (locucion->IndexOf("-") == i)
																	{
																		nueva_locucion += " - ";
																		String ^ aux = locucion;
																		locucion = aux->Substring(0, i);
																		locucion += " ";
																		locucion += aux->Substring(i + 1);
																		i++;
																	}
																	else
																	{
																		if (locucion->IndexOf("»") == i)
																		{
																			nueva_locucion += " » ";
																			String ^ aux = locucion;
																			locucion = aux->Substring(0, i);
																			locucion += " ";
																			locucion += aux->Substring(i + 1);
																			i++;
																		}
																		else
																		{
																			if (locucion->IndexOf("«") == i)
																			{
																				nueva_locucion += " « ";
																				String ^ aux = locucion;
																				locucion = aux->Substring(0, i);
																				locucion += " ";
																				locucion += aux->Substring(i + 1);
																				i++;
																			}
																			else
																			{
																				if (locucion->IndexOf("(") == i)
																				{
																					nueva_locucion += " ( ";
																					String ^ aux = locucion;
																					locucion = aux->Substring(0, i);
																					locucion += " ";
																					locucion += aux->Substring(i + 1);
																					i++;
																				}
																				else
																				{
																					if (locucion->IndexOf(")") == i)
																					{
																						nueva_locucion += " ) ";
																						String ^ aux = locucion;
																						locucion = aux->Substring(0, i);
																						locucion += " ";
																						locucion += aux->Substring(i + 1);
																						i++;
																					}
																					else
																					{
																						if (locucion->IndexOf("[") == i)
																						{
																							nueva_locucion += " [ ";
																							String ^ aux = locucion;
																							locucion = aux->Substring(0, i);
																							locucion += " ";
																							locucion += aux->Substring(i + 1);
																							i++;
																						}
																						else
																						{
																							if (locucion->IndexOf("]") == i)
																							{
																								nueva_locucion += " ] ";
																								String ^ aux = locucion;
																								locucion = aux->Substring(0, i);
																								locucion += " ";
																								locucion += aux->Substring(i + 1);
																								i++;
																							}
																							else
																							{
																								if (locucion->IndexOf("<") == i)
																								{
																									nueva_locucion += " < ";
																									String ^ aux = locucion;
																									locucion = aux->Substring(0, i);
																									locucion += " ";
																									locucion += aux->Substring(i + 1);
																									i++;
																								}
																								else
																								{
																									if (locucion->IndexOf(">") == i)
																									{
																										nueva_locucion += " > ";
																										String ^ aux = locucion;
																										locucion = aux->Substring(0, i);
																										locucion += " ";
																										locucion += aux->Substring(i + 1);
																										i++;
																									}
																									else
																									{
																										if (locucion->IndexOf("NOMBRE PROPIO") == i)
																										{
																											nueva_locucion += "NOMBRE_PROPIO";
																											String ^ aux = locucion;
																											locucion = aux->Substring(0, i);
																											locucion += "             ";
																											locucion += aux->Substring(i + 13);
																											i+=13;
																										}
																										else
																										{
																											if (locucion->IndexOf("IMPERFECTO DE SUBJUNTIVO") == i)
																											{
																												nueva_locucion += "IMP_SUBJUNTIVO";
																												String ^ aux = locucion;
																												locucion = aux->Substring(0, i);
																												locucion += "                        ";
																												locucion += aux->Substring(i + 24);
																												i+=24;
																											}
																											else
																											{
																												if (locucion->IndexOf(" d'") == i)
																												{
																													nueva_locucion += " de ";
																													String ^ aux = locucion;
																													locucion = aux->Substring(0, i);
																													locucion += "   ";
																													locucion += aux->Substring(i + 3);
																													i+=3;
																												}
																												else
																													nueva_locucion += locucion[i++];
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}																		
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}

			return nueva_locucion;
		}

		int TroceaTexto(String ^ texto)
		{
			int indice = texto->Length;

			if (texto->IndexOf('.') != -1 && texto->IndexOf('.') < indice)
				indice = texto->IndexOf('.');

			if (texto->IndexOf(',') != -1 && texto->IndexOf(',') < indice)
				indice = texto->IndexOf(',');

			if (texto->IndexOf('?') != -1 && texto->IndexOf('?') < indice)
				indice = texto->IndexOf('?');

			if (texto->IndexOf('¿') != -1 && texto->IndexOf('¿') < indice)
				indice = texto->IndexOf('¿');

			if (texto->IndexOf('¡') != -1 && texto->IndexOf('¡') < indice)
				indice = texto->IndexOf('¡');

			if (texto->IndexOf('!') != -1 && texto->IndexOf('!') < indice)
				indice = texto->IndexOf('!');

			if (texto->IndexOf(';') != -1 && texto->IndexOf(';') < indice)
				indice = texto->IndexOf(';');

			if (texto->IndexOf(':') != -1 && texto->IndexOf(':') < indice)
				indice = texto->IndexOf(':');

			if (texto->IndexOf('-') != -1 && texto->IndexOf('-') < indice)
				indice = texto->IndexOf('-');

			if (texto->IndexOf('(') != -1 && texto->IndexOf('(') < indice)
				indice = texto->IndexOf('(');

			if (texto->IndexOf(')') != -1 && texto->IndexOf(')') < indice)
				indice = texto->IndexOf(')');

			if (texto->IndexOf('[') != -1 && texto->IndexOf('[') < indice)
				indice = texto->IndexOf('[');

			if (texto->IndexOf(']') != -1 && texto->IndexOf(']') < indice)
				indice = texto->IndexOf(']');

			return indice;
		}


		//---------------------------------------------------------------------------
		//Función que, a partir de un fichero de texto dado, obtiene el análisis de cada
		//una de sus líneas y lo almacena en un fichero que tendrá el mismo nombre
		//pero con la extensión .xml
		bool AnalizaFicheros(String ^ nombre_fichero)
		{
			Directory::CreateDirectory("..\\Datos\\Out");

			String ^ ruta = "";
			String ^ ruta_fichero = "..\\Datos\\Out\\";
			String ^ directorio = "..\\Datos\\Out\\";
			char numero[10];
			String ^ parte_nombre;

			ruta = ruta->Copy(fich_path);
			ruta = ruta->Concat(ruta, nombre_fichero);

			//Se obtiene el nombre del fichero a crear
			//Se crean el fichero xml y una carpeta donde se almacenarán los resultados del mismo
			if (nombre_fichero->EndsWith(".txt"))
			{
				parte_nombre = nombre_fichero->Substring(0, nombre_fichero->Length - 4);
				String ^ fichero = "";
				fichero = fichero->Copy(nombre_fichero->Substring(0, parte_nombre->Length));
				ruta_fichero = ruta_fichero->Concat(ruta_fichero, fichero);

				if (art_pre)
					ruta_fichero = ruta_fichero + "_art_pre";
				ruta_fichero = ruta_fichero + ".xml";
			}
			else
				ruta_fichero = ruta_fichero->Concat(ruta_fichero, nombre_fichero);

			FileStream ^ f_xml = File::Create(ruta_fichero);
			Encoding ^ linea = Encoding::Default;

			String ^ linea_fichero = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
			int len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

			linea_fichero = "<resultado>\n";
			len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0,  len);

			//Se abre el fichero en modo lectura
			StreamReader ^ fd = gcnew StreamReader(ruta, System::Text::Encoding::GetEncoding("ISO-8859-1"));

			int n_linea = 1;

			String ^ texto = fd->ReadToEnd();
			FileStream ^ no_reconocidas = File::Create("..\\Datos\\Out\\no_reconocidas_" + nombre_fichero);
			std::vector<Info> n_recs;

			//mientras no se alcance el final del fichero
			while (texto->Length > 0)
			{
				std::vector< std::vector<Info> > Elementos;
				String ^ linea_texto;

				int indice = texto->IndexOf('.');
				if (indice != -1)
				{
					linea_texto = texto->Substring(0, indice + 1);
					if (indice + 1 < texto->Length)
						texto = texto->Substring(indice+1);
					else
						texto = "";
				}
				else
				{
					linea_texto = linea_texto->Copy(texto);
					texto = "";
				}

				linea_texto = QuitaSimbolos(linea_texto);

				if (linea_texto->Length > 0)
				{
					char * linea_c = (char*)(void*)Marshal::StringToHGlobalAnsi(linea_texto);
					if (linea_texto->Contains("\""))
						linea_texto = linea_texto->Replace("\"", "");
					linea_fichero = "\t<linea numero = \"" + n_linea.ToString() + "\" texto = \"" + linea_texto + "\">\n";
					len = linea_fichero->Length;
					f_xml->Write(linea->GetBytes(linea_fichero), 0,  len);

					String ^ locucion_formateada = FormateaLocucion(linea_texto);

					//Se analizan las palabras de la locución de forma independiente
					std::vector<char*> palabras_validas;
					std::vector<char*> palabras_pronombres;
					Elementos = AnalizaPalabras((char*)(void*)Marshal::StringToHGlobalAnsi(locucion_formateada), Elementos, "", &palabras_validas, &palabras_pronombres);					


					//Se escriben los resultados en el nuevo fichero
					if(Elementos.size() > 0)
					{                            
						int n_elementos = 1;
						for(int i = 0; i < Elementos.size(); i++)
						{
							if (Elementos[i].size() > 0)
							{								
								String ^ simbolo = gcnew String(Elementos[i][0].FormaCanonica);
								if (simbolo == "." || simbolo == "..." || simbolo == "," || simbolo == ";" || 
									simbolo == "¡" || simbolo == "!" || simbolo == "¿" || simbolo == "?" || 
									simbolo == "+" || simbolo == "'" || simbolo == ":" || simbolo == "`" ||
									simbolo == "%" || simbolo == "=" || simbolo == "-" || simbolo == "*" ||
									simbolo == "«" || simbolo == "»" || simbolo == "(" || simbolo == ")" || 
									simbolo == "[" || simbolo == "]" || simbolo == "<" || simbolo == ">" || 
									simbolo == "u.p." || simbolo == "u.c.")
									continue;
								String ^ palabra_actual = gcnew String(palabras_validas[i]);
								linea_fichero = "\t\t<elemento numero=\"" + n_elementos.ToString() + "\" texto=\"" + palabra_actual + "\">\n";
								n_elementos++;
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0,  len);
								for(int j = 0; j < Elementos[i].size(); j++)
								{
									int ind = j+1;
									String ^ forma_canonica = gcnew String(Elementos[i][j].FormaCanonica);
									linea_fichero = "\t\t\t<analisis linea=\"" + n_linea.ToString() + "\" numero=\"" + ind.ToString() + "\"";
									//forma_canonica
									linea_fichero += " FC=\"" + forma_canonica + "\"";
									//categoria) 
									linea_fichero += " CG=\"" + Elementos[i][j].Categoria.ToString() + "\"";
									//flexion
									linea_fichero += " FL=\"" + Elementos[i][j].Flexion.ToString() + "\"";
									//gen_num
									linea_fichero += " GN=\"" + Elementos[i][j].GenNum.ToString() + "\""; 
									//pronombre
									String ^ pronombre = gcnew String(Elementos[i][j].Pronombre);
									linea_fichero += " PR=\"" + pronombre + "\""; 
									linea_fichero += "/>\n";
									len = linea_fichero->Length;
									f_xml->Write(linea->GetBytes(linea_fichero), 0,  len);

									if (Elementos[i][j].Categoria == 0 && !EstaInfo(Elementos[i][j], n_recs))
									{
										n_recs.push_back(Elementos[i][j]);
										String ^ f_canonica = gcnew String(Elementos[i][j].FormaCanonica);
										if (f_canonica != "." && f_canonica != "..." && f_canonica != "," && f_canonica != ";" && 
											f_canonica != "¡" && f_canonica != "!" && f_canonica != "¿" && f_canonica != "?" && 
											f_canonica != "+" && f_canonica != "'" && f_canonica != ":" && f_canonica != "`" &&
											f_canonica != "%" && f_canonica != "=" && f_canonica != "-" && f_canonica != "*" && 											
											f_canonica != "«" && f_canonica != "»" && f_canonica != "(" && f_canonica != ")" && 
											f_canonica != "[" && f_canonica != "]" && f_canonica != "<" && f_canonica != ">")
										{
											try
											{
												Convert::ToInt32(f_canonica);
											}
											catch (Exception ^ ex)
											{
												String ^ linea_nr = "\"" + f_canonica + "\" en locución " + i.ToString() + "\n";
												no_reconocidas->Write(linea->GetBytes(linea_nr), 0, linea_nr->Length);
											}
										}
									}
								}
								linea_fichero = "\t\t</elemento>\n";
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0,  len);
							}
						}
					}	

					n_linea++;
					linea_fichero = "\t</linea>\n";
					len = linea_fichero->Length;
					f_xml->Write(linea->GetBytes(linea_fichero), 0,  len);
				}
			}

			linea_fichero = "</resultado>\n";
			len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0,  len);

			f_xml->Close();
			fd->Close();
			no_reconocidas->Close();

			return true;
		}

		void ExtraeEjemplosVarela()
		{
			XmlDocument ^ xmldoc = gcnew XmlDocument();
			xmldoc->Load("..\\Datos\\In\\varela_mine.xml");
			FileStream ^ fd = File::Create("..\\Datos\\In\\Ficheros\\" + f_ejemplos);

			XmlNode ^ doc_elem = xmldoc->DocumentElement;
			String ^ doc_cond = "//ejemplo";
			XmlNodeList ^ ejemploList = doc_elem->SelectNodes(doc_cond);
			System::Collections::IEnumerator^ ejemploEnum = ejemploList->GetEnumerator();

			String ^ linea_fichero;
			int len = 0;
			Encoding ^ linea = Encoding::Default;

			while( ejemploEnum->MoveNext())
			{
				XmlNode ^ nodoEjemplo = safe_cast<XmlNode^>(ejemploEnum->Current);

				linea_fichero = QuitaSimbolos(nodoEjemplo->InnerText) + ".\n";
				len = linea_fichero->Length;
				fd->Write(linea->GetBytes(linea_fichero), 0, len);
			}

			fd->Close();
		}

		void AnalizaLocucionesVarela(FileStream ^ no_reconocidas)
		{
			/*XmlDocument ^ xmldoc = gcnew XmlDocument();
			xmldoc->Load("..\\Datos\\In\\varela_mine.xml");
			FileStream ^ fd = File::Create(f_locs_varela);

			XmlNode ^ doc_elem = xmldoc->DocumentElement;
			String ^ doc_cond = "//clave";
			XmlNodeList ^ claveList = doc_elem->SelectNodes(doc_cond);
			System::Collections::IEnumerator^ claveEnum = claveList->GetEnumerator();

			String ^ linea_fichero = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
			int len = linea_fichero->Length;
			Encoding ^ linea = Encoding::Default;

			fd->Write(linea->GetBytes(linea_fichero), 0, len);
			linea_fichero = "<locuciones>\n";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);

			while( claveEnum->MoveNext())
			{
			XmlNode ^ nodoClave = safe_cast<XmlNode^>(claveEnum->Current);

			int len = 0;
			//int n_locucion = 1;

			linea_fichero = "\t<locucion clave = \"" + QuitaSimbolos(nodoClave->InnerText) + "\">\n";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);

			for (int i = 0; i < nodoClave->ParentNode->ChildNodes->Count; i++)
			{
			XmlNode ^ childNode = nodoClave->ParentNode->ChildNodes[i];

			if (childNode->Name == "locucion")
			{
			for(int j = 0; j < childNode->ChildNodes->Count; j++)
			{
			XmlNode ^ nodoTexto = childNode->ChildNodes[j];

			if (nodoTexto->Name == "texto")
			{
			std::vector< std::vector<char *> > locuciones;
			int n_opciones[MAX_PAL];
			String ^ espacio = " ";
			int n_palabras = 0;

			locuciones = ObtieneLocucionesVarela((char*)(void*)Marshal::StringToHGlobalAnsi(nodoTexto->InnerText));

			linea_fichero = "\t\t<texto loc = \"" + QuitaSimbolos(nodoTexto->InnerText) + "\">\n ";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);
			//Se escriben las nuevas locuciones obtenidas en el fichero "locuciones.txt"
			for(int j = 0; j < locuciones.size(); j++)
			{
			int n_locucion = j + 1;
			linea_fichero = "\t\t\t<opcion numero = \"" + n_locucion.ToString() + "\"> ";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);
			for (int k = 0; k < locuciones[j].size(); k++)
			{		
			String ^ trozo = QuitaSimbolos(gcnew String(locuciones[j][k]));
			locuciones[j][k] = (char*)(void*)Marshal::StringToHGlobalAnsi(trozo);
			if (strcmp(locuciones[j][k], "") && strcmp(locuciones[j][k], " "))
			{
			len = strlen(locuciones[j][k]);
			array<Byte>^ charArray = gcnew array<Byte>(len + 2);
			Marshal::Copy((IntPtr)locuciones[j][k],charArray, 0, len);
			fd->Write(charArray, 0, len);
			len = espacio->Length;
			fd->Write(linea->GetBytes(espacio), 0, len);
			delete [] charArray;
			}
			}

			linea_fichero = "</opcion>\n";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);
			//n_locucion++;
			}								
			linea_fichero = "\t\t</texto>\n";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);
			break;
			}
			}
			}
			}

			linea_fichero = "\t</locucion>\n";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);
			}

			linea_fichero = "</locuciones>\n";
			len = linea_fichero->Length;
			fd->Write(linea->GetBytes(linea_fichero), 0, len);

			fd->Close();*/

			//Se abre el fichero "locuciones.xml" en modo lectura
			//StreamReader ^ f = gcnew StreamReader(f_locs, System::Text::Encoding::GetEncoding("ISO-8859-1"));
			//Se carga el fichero de resultados del texto a probar
			XmlDocument ^ locs_xmldoc = gcnew XmlDocument();
			locs_xmldoc->Load(f_locs_varela);
			XmlNode ^ locs_doc_elem = locs_xmldoc->DocumentElement;
			String ^ locs_doc_cond = "//opcion";
			XmlNodeList ^ locucionesList = locs_doc_elem->SelectNodes(locs_doc_cond);

			System::Collections::IEnumerator^ locucionesEnum = locucionesList->GetEnumerator();

			FileStream ^ f_xml;
			if (art_pre)
				f_xml = File::Create(f_res_varela_base_art_pre);
			else
				f_xml = File::Create(f_res_varela_base);

			String ^ linea_fichero = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
			int len = linea_fichero->Length;
			Encoding ^ linea = Encoding::Default;

			f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
			linea_fichero = "<resultado>\n";
			len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

			int i = 0;
			std::vector<Info> n_recs;

			//Para cada coincidencia encontrada
			while ( locucionesEnum->MoveNext() )
			{		
				XmlNode^ nodo = safe_cast<XmlNode^>(locucionesEnum->Current);

				String ^ locucion = nodo->InnerText;//f->ReadLine();		

				while (locucion->Length > 0)
				{ 
					std::vector< std::vector<Info> > Elementos;
					std::vector< std::vector<Info> > combinaciones;

					i++;

					String ^ item_clave = nodo->ParentNode->ParentNode->Attributes["clave"]->Value->ToString();
					String ^ id_original = nodo->ParentNode->Attributes["numero"]->Value->ToString();

					linea_fichero = "\t<locucion id_locucion = \"" + id_original + "\" id = \"" + i.ToString() +  "\" clave = \"" + item_clave + "\" texto = \"" + locucion + "\">\n";
					len = linea_fichero->Length;
					f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

					String ^ locucion_formateada = FormateaLocucion(locucion);
					//locucion_formateada = locucion_formateada->Replace("u.p.", "...");
					//locucion_formateada = locucion_formateada->Replace("u.c.", "...");
					//locucion_formateada = locucion_formateada->Replace(" algo ", " ... ");
					//locucion_formateada = locucion_formateada->Replace(" alguien ", " ... ");
					locucion_formateada = locucion_formateada->Replace(" algo ", " u.c. ");
					locucion_formateada = locucion_formateada->Replace(" alguien ", " u.p. ");


					//Se analizan las palabras de la locución de forma independiente
					std::vector<char*> palabras_validas;
					std::vector<char*> palabras_pronombres;
					Elementos = AnalizaPalabras((char*)(void*)Marshal::StringToHGlobalAnsi(locucion_formateada), Elementos, item_clave, &palabras_validas, &palabras_pronombres);					

					//y se escriben todas las combinaciones posibles de resultados
					//en el fichero a continuación

					int numero_palabra = 0;
					//Se realizan todas las combinaciones posibles de los análisis obtenidos con anterioridad
					for (int j = 0; j < Elementos.size(); j++)
					{
						if (Elementos[j].size() > 0)
						{
							String ^ es_clave;
							if (Elementos[j][0].Clave)
								es_clave = "true";
							else
								es_clave = "false";
							String ^ simbolo = gcnew String(Elementos[j][0].FormaCanonica);
							if (simbolo == "." || simbolo == "," || simbolo == ";" || 
								simbolo == "¡" || simbolo == "!" || simbolo == "¿" || simbolo == "?" || 
								simbolo == "+" || simbolo == "'" || simbolo == ":" || simbolo == "`" ||
								simbolo == "%" || simbolo == "=" || simbolo == "-" || simbolo == "*" ||
								simbolo == "«" || simbolo == "»" || simbolo == "(" || simbolo == ")" || 
								simbolo == "[" || simbolo == "]" || simbolo == "<" || simbolo == ">" || 
								simbolo == "u.p." || simbolo == "u.c." || simbolo == "algo" || 
								simbolo == "alguien")
								continue;
							numero_palabra++;
							String ^ palabra_actual = gcnew String(palabras_validas[j]);
							linea_fichero = "\t\t<palabra numero = \"" + numero_palabra.ToString() + "\" clave = \"" +  es_clave + "\" texto = \"" + palabra_actual + "\"> \n";
							len = linea_fichero->Length;
							f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

							for(int k = 0; k < Elementos[j].size(); k++)
							{
								//Si se trata de una palabra no reconocida la guardamos
								if (Elementos[j][k].Categoria == 0 && !EstaInfo(Elementos[j][k], n_recs))
								{
									n_recs.push_back(Elementos[j][k]);
									String ^ f_canonica = gcnew String(Elementos[j][k].FormaCanonica);									
									if (f_canonica != "." && f_canonica != "..." && f_canonica != "," && f_canonica != ";" && 
										f_canonica != "¡" && f_canonica != "!" && f_canonica != "¿" && f_canonica != "?" && 
										f_canonica != "+" && f_canonica != "'" && f_canonica != ":" && f_canonica != "`" &&
										f_canonica != "%" && f_canonica != "=" && f_canonica != "-" && f_canonica != "*" && 											
										f_canonica != "«" && f_canonica != "»" && f_canonica != "(" && f_canonica != ")" && 
										f_canonica != "[" && f_canonica != "]" && f_canonica != "<" && f_canonica != ">" &&
										f_canonica != "u.p." && f_canonica != "u.c.")
									{
										String ^ linea_nr = "\"" + f_canonica + "\" en locución varela " + i.ToString() + "\n";
										no_reconocidas->Write(linea->GetBytes(linea_nr), 0, linea_nr->Length);
									}
								}	
								else
								{
									if (EsPronombrePersonal(Elementos[j][k].Categoria))
										strcpy(Elementos[j][k].FormaCanonica, "");
								}

								int numero_analisis = k+1;
								linea_fichero = "\t\t\t<analisis numero = \"" + numero_analisis.ToString() + "\" ";
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

								len = strlen(Elementos[j][k].FormaCanonica);
								array<Byte>^ charArray = gcnew array<Byte>(len + 2);
								Marshal::Copy((IntPtr)Elementos[j][k].FormaCanonica,charArray, 0, len);

								//forma_canonica
								linea_fichero = "FC = \"";
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
								len = strlen(Elementos[j][k].FormaCanonica);
								f_xml->Write(charArray, 0, len);
								linea_fichero = "\" "; 
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

								//categoria
								linea_fichero = "CG = \"" + Elementos[j][k].Categoria.ToString();
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
								linea_fichero = "\" "; 
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

								//flexion
								linea_fichero = "FL = \"" + Elementos[j][k].Flexion.ToString();
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
								linea_fichero = "\" "; 
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

								//gen_num
								linea_fichero = "GN = \"" + Elementos[j][k].GenNum.ToString(); + "\"/>\n";
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
								linea_fichero = "\" "; 
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

								//pronombre
								linea_fichero = "PR = \"";
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
								len = strlen(Elementos[j][k].Pronombre);
								charArray = gcnew array<Byte>(len + 2);
								Marshal::Copy((IntPtr)Elementos[j][k].Pronombre,charArray, 0, len);
								f_xml->Write(charArray, 0, len);
								linea_fichero = "\" "; 
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

								linea_fichero = "/>\n"; 
								len = linea_fichero->Length;
								f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

							}	

							linea_fichero = "\t\t</palabra>\n";
							len = linea_fichero->Length;
							f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
						}
					}

					linea_fichero = "\t</locucion>\n";
					len = linea_fichero->Length;
					f_xml->Write(linea->GetBytes(linea_fichero), 0, len);					

					locucion = "";

					if (palabras_pronombres.size() > 0)
					{
						for(int i = 0; i < palabras_pronombres.size(); i++)
							locucion += gcnew String(palabras_pronombres[i]) + " ";
					}
				}
			}

			linea_fichero = "</resultado>\n";
			len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

			f_xml->Close();
		}

		String ^ DevuelveEtiqueta(bool parametro)
		{
			String ^ valor = "false";

			if (parametro)
				valor = "true";

			return valor;
		}

		String ^ CreaCondicion()
		{
			String ^ condicion = "@FC='" + DevuelveEtiqueta(forma_canonica) +
				"' and @CG = '" + DevuelveEtiqueta(categoria) + 
				"' and @GN = '" + DevuelveEtiqueta(gen_num) + 
				"' and @FL = '" + DevuelveEtiqueta(flexion) + 
				"' and @ART_PRE = '" + DevuelveEtiqueta(art_pre) + 
				"' and @PR = '" + DevuelveEtiqueta(pronombre) + "'";

			return condicion;
		}

		String ^ CreaCondicionCorta()
		{
			String ^ condicion = "FC, CG, "; 

			if (gen_num)
				condicion += "GN, ";
			if (flexion)
				condicion += "FL, ";
			if (art_pre)
				condicion += "ART_PRE, ";
			if (pronombre)
				condicion += "PR";
			else
				condicion = condicion->Substring(0, condicion->Length - 2);

			return condicion;
		}

		int ObtieneNumeroResultados(XmlNode ^ documento)
		{
			String ^ doc_cond = "//child::locucion[child::opcion[child::linea[child::tipo[(";
			doc_cond += CreaCondicion();
			doc_cond += ")]]]]";

			XmlNodeList ^ coincidenciaList = documento->SelectNodes(doc_cond);

			return coincidenciaList->Count;
		}

		void ObtieneEstadisticas(XmlDocument ^ results, String ^ fichero)
		{
			XmlDocument ^ xmldoc = gcnew XmlDocument();
			xmldoc->Load(fichero);
			XmlNode ^ doc_elem = xmldoc->DocumentElement;
			String ^ doc_cond = "//child::locucion";
			XmlNodeList ^ coincidenciaList = doc_elem->SelectNodes(doc_cond);
			XmlNode ^ root = results->DocumentElement;
			String ^ condicion = "//resultado";
			XmlNodeList ^ index = root->SelectNodes(condicion);

			XmlAttribute ^ FicheroAttr = results->CreateAttribute("nombre");
			FicheroAttr->Value = fichero;
			XmlAttribute ^ NLocsAttr = results->CreateAttribute("n_locs");
			NLocsAttr->Value = coincidenciaList->Count.ToString();

			XmlElement ^ elem_fichero = results->CreateElement( "fichero" );
			elem_fichero->Attributes->Append(FicheroAttr);
			elem_fichero->Attributes->Append(NLocsAttr);

			forma_canonica = true;
			categoria = true;
			flexion = true;
			gen_num = true;
			pronombre = true;
			art_pre = true;

			int n_results = ObtieneNumeroResultados(doc_elem);

			XmlAttribute ^ CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			XmlAttribute ^ NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			XmlElement ^ elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			art_pre = false;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			pronombre = false;
			art_pre = true;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			art_pre = false;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			gen_num = false;
			pronombre = true;
			art_pre = true;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			art_pre = false;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			pronombre = false;
			art_pre = true;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			art_pre = false;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			flexion = false;
			gen_num = true;
			pronombre = true;
			art_pre = true;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			art_pre = false;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			pronombre = false;
			art_pre = true;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			art_pre = false;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			gen_num = false;
			pronombre = true;
			art_pre = true;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			art_pre = false;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			pronombre = false;
			art_pre = true;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			art_pre = false;

			n_results = ObtieneNumeroResultados(doc_elem);

			CombAttr = results->CreateAttribute("combinacion");
			CombAttr->Value = CreaCondicionCorta();
			NCoincidenciasAttr = results->CreateAttribute("coincidencias");
			NCoincidenciasAttr->Value = n_results.ToString();

			elem_combinacion = results->CreateElement( "tipo" );
			elem_combinacion->Attributes->Append(CombAttr);
			elem_combinacion->Attributes->Append(NCoincidenciasAttr);

			elem_fichero->AppendChild(elem_combinacion);

			root->AppendChild(elem_fichero);

		}

		//---------------------------------------------------------------------------
		//Procedimiento que, a partir de un fichero de resultados de un texto y el fichero de
		//resultados de las locuciones de la base de datos, busca las coincidencias existentes entre los mismos.
		//Para cada análisis de la base de datos con el que encuentre coincidencia en el fichero de texto
		//creará un nuevo documento en el que indicará las líneas en las que ha habido coincidencia.
		void BuscaCoincidencias(String ^ fichero, String ^ f_res, XmlDocument ^ comparativa_doc)
		{
			String ^ nombre_resultados;

			String ^ fichero_loc_actual = "..\\Datos\\Out\\locucion_actual.txt";

			FileStream ^ f_xml = File::Create(fichero_loc_actual);
			Encoding ^ linea = Encoding::Default;

			String ^ linea_fichero = "0\n";
			int len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
			f_xml->Close();

			String ^ nombre_fichero = gcnew String(fichero);
			XmlNode ^ comparativa_xml = comparativa_doc->DocumentElement;
			XmlNode^ root = comparativa_doc->DocumentElement;

			if (nombre_fichero->EndsWith(".txt"))
			{
				int indice = nombre_fichero->IndexOf(".txt");
				nombre_fichero = nombre_fichero->Substring(0, indice);
			}
			if (art_pre)
				nombre_fichero = nombre_fichero + "_art_pre";
			nombre_fichero = nombre_fichero + ".xml";

			String ^ ruta_fichero = "..\\Datos\\Out\\";
			ruta_fichero = ruta_fichero->Concat(ruta_fichero, nombre_fichero);

			//Se carga el fichero de resultados del texto a probar
			XmlDocument ^ xmldoc = gcnew XmlDocument();
			xmldoc->Load(f_res);
			XmlNode ^ doc_elem = xmldoc->DocumentElement;
			String ^ doc_cond = "//palabra[@clave='true']";
			XmlNodeList ^ claveList = doc_elem->SelectNodes(doc_cond);

			//Se carga el fichero de resultados de las locuciones de la base de datos
			XmlDocument ^ xmlfichero = gcnew XmlDocument();
			xmlfichero->Load(ruta_fichero);
			XmlNode ^ fich_elem = xmlfichero->DocumentElement;

			System::Collections::IEnumerator^ claveEnum = claveList->GetEnumerator();
			String ^ numero_locucion = "";

			//Para cada coincidencia encontrada
			while ( claveEnum->MoveNext() )
			{
				XmlNode ^ nodoClave = safe_cast<XmlNode^>(claveEnum->Current);
				if (nodoClave->ParentNode->Attributes["id"]->Value->ToString() == numero_locucion)
					continue;
				else
					numero_locucion = nodoClave->ParentNode->Attributes["id"]->Value->ToString();
				f_xml = gcnew FileStream("..\\Datos\\Out\\locucion_actual.txt", FileMode::Open);
				linea_fichero = numero_locucion + "\n";
				len = linea_fichero->Length;
				f_xml->Write(linea->GetBytes(linea_fichero), 0, len);
				f_xml->Close();

				XmlNodeList ^ analisisList = nodoClave->ChildNodes;
				System::Collections::IEnumerator^ analisisEnum = analisisList->GetEnumerator();
				String ^ cond = "//child::linea[child::elemento[child::analisis[";
				int hijos = 0;
				//FILE * f_coincidencias = NULL;
				//Para cada coincidencia encontrada
				while( analisisEnum->MoveNext())
				{
					try
					{
						XmlNode ^ nodoAnalisis = safe_cast<XmlNode^>(analisisEnum->Current);

						int elementos = 0;

						if (hijos > 0)
							cond += " or ";
						hijos++;
						if (forma_canonica && nodoAnalisis->Attributes["FC"]->Value->ToString() != "") 
						{
							String ^ fc = nodoAnalisis->Attributes["FC"]->Value->ToString();
							if (fc->Contains("'")) 
								fc = fc->Replace("'"," "); 
							cond += "(@FC='" + fc + "'";
							elementos++;
						}

						if (categoria && nodoAnalisis->Attributes["CG"]->Value->ToString() != "0")
						{
							if (elementos > 0)
								cond += " and ";
							else 
								cond += "(";
							cond += "@CG='" + nodoAnalisis->Attributes["CG"]->Value->ToString() + "'";
							elementos++;
						}

						if (flexion)
						{
							if (nodoAnalisis->Attributes["FL"]->Value->ToString() != "0")
							{
								if (elementos > 0)
									cond += " and ";
								else 
									cond += "(";
								cond += "@FL='" + nodoAnalisis->Attributes["FL"]->Value->ToString()+ "'";
								elementos++;
							}
						}
						else
						{
							//OBLIGA A QUE SI EL VERBO ES DISTINTO DE INFINITIVO SE COMPARE LA FLEXIÓN
							int valor = Convert::ToInt32(nodoAnalisis->Attributes["CG"]->Value->ToString());
							bool contiene = false;
							for(int ind = 0; ind < v_categorias[8].size(); ind++)
							{
								if (valor != 0 && v_categorias[8][ind] == valor)
								{
									contiene = true;
									break;
								}
							}

							if (contiene && categoria)
							{
								if (nodoAnalisis->Attributes["FL"]->Value->ToString() != "0")
								{
									if (elementos > 0)
										cond += " and ";
									else 
										cond += "(";
									cond += "@FL='" + nodoAnalisis->Attributes["FL"]->Value->ToString()+ "'";
									elementos++;
								}
							}
						}

						if (gen_num && nodoAnalisis->Attributes["GN"]->Value->ToString() != "0")
						{
							if (elementos > 0)
								cond += " and ";
							else 
								cond += "(";
							cond += "@GN='" + nodoAnalisis->Attributes["GN"]->Value->ToString() + "'";
							elementos++;
						}

						if (pronombre && nodoAnalisis->Attributes["PR"]->Value->ToString() != "") 
						{
							String ^ pr = nodoAnalisis->Attributes["PR"]->Value->ToString();
							if (pr->Contains("'")) 
								pr = pr->Replace("'"," "); 
							if (elementos > 0)
								cond += " and ";
							else 
								cond += "(";
							cond += "@PR='" + pr + "'";
							elementos++;
						}

						if (elementos > 0)
							cond += ")";
					}
					catch (std::exception& ex)
					{
						throw ex;
					}
				}
				cond += "]]]";

				if (hijos == 0) continue;

				XmlNodeList ^ nodeList = fich_elem->SelectNodes(cond);

				System::Collections::IEnumerator^ myEnum = nodeList->GetEnumerator();

				/*En nodeList tengo la lista de análisis que coinciden con el análisis de la palabra clave que 
				se está analizando*/
				//Para cada coincidencia encontrada
				while (myEnum->MoveNext() )
				{
					try
					{
						XmlNode ^ analisis = safe_cast<XmlNode^>(myEnum->Current);

						//número de palabras que tiene la línea en la que se ha encontrado la coincidencia
						int nodos = analisis->ChildNodes->Count;
						int nodos_p_suspensivos = 0;

						XmlNode ^ nodoLocucion = nodoClave->ParentNode;
						int n_clave = Convert::ToInt32(nodoLocucion->Attributes["id"]->Value->ToString());

						if (nodos >= nodoLocucion->ChildNodes->Count)
						{
							//Para cada palabra de la locución
							std::vector < std::vector<int> > vector_coincidencias;
							int posicion = 0;
							bool coincidencia = true;
							bool puntos_suspensivos = false;
							for(int l = 0; l < nodoLocucion->ChildNodes->Count; l++)
							{
								XmlNode ^ nodoPalabra = nodoLocucion->ChildNodes[l];
								std::vector<int> posiciones;
								std::vector<char*> fc_list;
								std::vector<char*> cg_list;								
								std::vector<char*> fl_list;
								std::vector<char*> gn_list;								
								std::vector<char*> pr_list;
								cond = "//child::elemento[child::analisis[";

								String ^ fc = "";
								String ^ cg = "";
								String ^ fl = "";
								String ^ gn = "";
								String ^ pr = "";

								//Para cada análisis obtenido de cada palabra
								for( int m = 0; m < nodoPalabra->ChildNodes->Count; m++)
								{
									XmlNode ^ nodoAnalisisPalabra = nodoPalabra->ChildNodes[m];

									//Si se encuentran puntos suspensivos, se sigue avanzando por la locución 
									//admitiendo todas las palabras o símbolos hasta encontrar coincidencia con 
									//la siguiente
									if (nodoAnalisisPalabra->Attributes["FC"]->Value->ToString() == "...")
									{
										puntos_suspensivos = true;
										nodos_p_suspensivos++;
										cond = "";
										break;
									}

									if (forma_canonica && nodoAnalisisPalabra->Attributes["FC"]->Value->ToString() != "")
									{
										bool esta = false;
										String ^ fc_item = nodoAnalisisPalabra->Attributes["FC"]->Value->ToString();
										IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(fc_item);
										char* a = static_cast<char*>(ptrToNativeString.ToPointer());

										for(int index = 0; index < fc_list.size(); index++)
										{
											if (strcmp(fc_list[index], a) == 0)
											{
												esta = true;
												break;
											}
										}
										if (!esta)
										{
											fc_list.push_back(a);
											if (fc == "")
												fc += "(@FC='" + nodoAnalisisPalabra->Attributes["FC"]->Value->ToString() + "'";
											else 
												fc += " or @FC='" + nodoAnalisisPalabra->Attributes["FC"]->Value->ToString() + "'";
										}
									}
									if (categoria && nodoAnalisisPalabra->Attributes["CG"]->Value->ToString() != "0")
									{
										bool esta = false;
										String ^ cg_item = nodoAnalisisPalabra->Attributes["CG"]->Value->ToString();
										IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(cg_item);
										char* a = static_cast<char*>(ptrToNativeString.ToPointer());

										for(int index = 0; index < cg_list.size(); index++)
										{
											if (strcmp(cg_list[index], a) == 0)
											{
												esta = true;
												break;
											}
										}
										if (!esta)
										{
											cg_list.push_back(a);
											if (cg == "")
												cg += "(@CG='" + nodoAnalisisPalabra->Attributes["CG"]->Value->ToString() + "'";
											else											
												cg += " or @CG='" + nodoAnalisisPalabra->Attributes["CG"]->Value->ToString() + "'";
										}
									}

									if (flexion)
									{
										if (nodoAnalisisPalabra->Attributes["FL"]->Value->ToString() != "0")
										{
											bool esta = false;
											String ^ fl_item = nodoAnalisisPalabra->Attributes["FL"]->Value->ToString();
											IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(fl_item);
											char* a = static_cast<char*>(ptrToNativeString.ToPointer());

											for(int index = 0; index < fl_list.size(); index++)
											{
												if (strcmp(fl_list[index], a) == 0)
												{
													esta = true;
													break;
												}
											}
											if (!esta)
											{
												fl_list.push_back(a);
												if (fl == "")
													fl += "(@FL='" + nodoAnalisisPalabra->Attributes["FL"]->Value->ToString() + "'";
												else 
													fl += " or @FL='" + nodoAnalisisPalabra->Attributes["FL"]->Value->ToString() + "'";
											}
										}
									}
									else
									{
										//OBLIGA A QUE SI EL VERBO ES DISTINTO DE INFINITIVO SE COMPARE LA FLEXIÓN
										int valor = Convert::ToInt32(nodoAnalisisPalabra->Attributes["CG"]->Value->ToString());
										bool contiene = false;
										for(int ind = 0; ind < v_categorias[8].size(); ind++)
										{
											if (valor != 0 && v_categorias[8][ind] == valor)
											{
												contiene = true;
												break;
											}
										}

										if (contiene && categoria)
										{
											if (nodoAnalisisPalabra->Attributes["FL"]->Value->ToString() != "0")
											{
												bool esta = false;
												String ^ fl_item = nodoAnalisisPalabra->Attributes["FL"]->Value->ToString();
												IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(fl_item);
												char* a = static_cast<char*>(ptrToNativeString.ToPointer());

												for(int index = 0; index < fl_list.size(); index++)
												{
													if (strcmp(fl_list[index], a) == 0)
													{
														esta = true;
														break;
													}
												}
												if (!esta)
												{
													fl_list.push_back(a);
													if (fl == "")
														fl += "(@FL='" + nodoAnalisisPalabra->Attributes["FL"]->Value->ToString() + "'";
													else 
														fl += " or @FL='" + nodoAnalisisPalabra->Attributes["FL"]->Value->ToString() + "'";
												}
											}
										}
									}

									if (gen_num && nodoAnalisisPalabra->Attributes["GN"]->Value->ToString() != "0")
									{
										bool esta = false;
										String ^ gn_item = nodoAnalisisPalabra->Attributes["GN"]->Value->ToString();
										IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(gn_item);
										char* a = static_cast<char*>(ptrToNativeString.ToPointer());

										for(int index = 0; index < gn_list.size(); index++)
										{
											if (strcmp(gn_list[index], a) == 0)
											{
												esta = true;
												break;
											}
										}
										if (!esta)
										{
											gn_list.push_back(a);
											if (gn == "")
												gn += "(@GN='" + nodoAnalisisPalabra->Attributes["GN"]->Value->ToString() + "'";
											else 
												gn += " or @GN='" + nodoAnalisisPalabra->Attributes["GN"]->Value->ToString() + "'";
										}
									}
									if (pronombre && nodoAnalisisPalabra->Attributes["PR"]->Value->ToString() != "")
									{
										bool esta = false;
										String ^ pr_item = nodoAnalisisPalabra->Attributes["PR"]->Value->ToString();
										IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(pr_item);
										char* a = static_cast<char*>(ptrToNativeString.ToPointer());

										for(int index = 0; index < pr_list.size(); index++)
										{
											if (strcmp(pr_list[index], a) == 0)
											{
												esta = true;
												break;
											}
										}
										if (!esta)
										{
											pr_list.push_back(a);
											if (pr == "")
												pr += "(@PR='" + nodoAnalisisPalabra->Attributes["PR"]->Value->ToString() + "'";
											else
												pr += " or @PR='" + nodoAnalisisPalabra->Attributes["PR"]->Value->ToString() + "'";
										}
									}
								}

								if (!coincidencia)
									break;

								if (cond == "") continue;

								cond += "@linea='" + analisis->Attributes["numero"]->Value->ToString() + "'";

								if (fc != "") cond += " and " + fc + ")";
								if (cg != "") cond += " and " + cg + ")";
								if (fl != "") cond += " and " + fl + ")";
								if (gn != "") cond += " and " + gn + ")";
								if (pr != "") cond += " and " + pr + ")";

								cond += "]]";

								cond = cond->Replace(" d'", " de ");

								XmlNodeList ^ l_coincidencias = fich_elem->SelectNodes(cond);
								System::Collections::IEnumerator^ myItems = l_coincidencias->GetEnumerator();
								//Para cada coincidencia encontrada
								while ( myItems->MoveNext() )
								{
									XmlNode ^ Item = safe_cast<XmlNode^>(myItems->Current);	
									posiciones.push_back(Convert::ToInt32(Item->Attributes["numero"]->Value->ToString()));
								}

								if (posiciones.size() > 0)
								{
									vector_coincidencias = CombinaPosiciones(posiciones, vector_coincidencias, puntos_suspensivos);
									if (vector_coincidencias.size() > 0)
									{
										coincidencia = true;
										puntos_suspensivos = false;
									}
									else
									{
										coincidencia = false;
										break;
									}
								}
								else
								{
									coincidencia = false;
									break;
								}
							}

							if (coincidencia && 
								(nodos_p_suspensivos + vector_coincidencias[0].size() == nodoLocucion->ChildNodes->Count))
							{
								std::vector<char *> textos_coincidentes;
								String ^ texto_coincidente = "";

								for(int y = 0; y < vector_coincidencias.size(); y++)
								{
									for(int x = 0; x < vector_coincidencias[y].size(); x++)
										texto_coincidente += analisis->ChildNodes[vector_coincidencias[y][x] - 1]->Attributes["texto"]->Value->ToString() + " ";

									char * texto = new char[MAX_LON_ORA];
									strcpy(texto, (char*)(void*)Marshal::StringToHGlobalAnsi(texto_coincidente));
									if (texto_coincidente->Length > 0 && 
										!EstaTexto(texto, textos_coincidentes))
									{
										textos_coincidentes.push_back(texto);
									}
									texto_coincidente = "";
								}

								texto_coincidente = "";

								for(int x = 0; x < textos_coincidentes.size(); x++)
								{
									String ^ texto = gcnew String(textos_coincidentes[x]);
									if (texto_coincidente->Length > 0)
										texto_coincidente += "/ ";
									texto_coincidente += texto;
								}

								//Busca en el fichero que almacena los resultados de todas las pruebas, que ya existan resultados para la locución actual
								String ^ condicion_comparativa = "//locucion[@numero='" + nodoLocucion->Attributes["id_locucion"]->Value->ToString() + "']";
								XmlNodeList ^ locucion_comparativa = comparativa_xml->SelectNodes(condicion_comparativa);

								if (locucion_comparativa->Count > 0)
								{
									//Busca en el fichero que almacena los resultados de todas las pruebas, que ya existan resultados para la locución actual
									condicion_comparativa = "//opcion[@numero='" + nodoLocucion->Attributes["id"]->Value->ToString() + "']";
									XmlNodeList ^ opcion_comparativa = comparativa_xml->SelectNodes(condicion_comparativa);

									if (opcion_comparativa->Count > 0)
									{
										condicion_comparativa = "//linea[@numero='" + analisis->Attributes["numero"]->Value->ToString() 
											+ "' and parent::opcion[@numero='" + nodoLocucion->Attributes["id"]->Value->ToString() + "']]";
										XmlNodeList ^ linea_comparativa = comparativa_xml->SelectNodes(condicion_comparativa);

										if (linea_comparativa->Count > 0)
										{
											XmlNode ^ elem_linea = linea_comparativa[0];

											//Agregar nodo tipo
											XmlAttribute ^ TextoAttr = comparativa_doc->CreateAttribute("texto");
											TextoAttr->Value = texto_coincidente;
											XmlAttribute ^ FCAttr = comparativa_doc->CreateAttribute("FC");
											if (forma_canonica)
												FCAttr->Value = "true";
											else
												FCAttr->Value = "false";
											XmlAttribute ^ CGAttr = comparativa_doc->CreateAttribute("CG");
											if (categoria)
												CGAttr->Value = "true";
											else
												CGAttr->Value = "false";
											XmlAttribute ^ GNAttr = comparativa_doc->CreateAttribute("GN");
											if (gen_num)
												GNAttr->Value = "true";
											else
												GNAttr->Value = "false";
											XmlAttribute ^ FLAttr = comparativa_doc->CreateAttribute("FL");
											if (flexion)
												FLAttr->Value = "true";
											else
												FLAttr->Value = "false";
											XmlAttribute ^ ART_PREAttr = comparativa_doc->CreateAttribute("ART_PRE");
											if (art_pre)
												ART_PREAttr->Value = "true";
											else
												ART_PREAttr->Value = "false";
											XmlAttribute ^ PRAttr = comparativa_doc->CreateAttribute("PR");
											if (pronombre)
												PRAttr->Value = "true";
											else
												PRAttr->Value = "false";

											XmlElement ^ elem_tipo = comparativa_doc->CreateElement( "tipo" );
											elem_tipo->Attributes->Append(TextoAttr);
											elem_tipo->Attributes->Append(FCAttr);
											elem_tipo->Attributes->Append(CGAttr);
											elem_tipo->Attributes->Append(GNAttr);
											elem_tipo->Attributes->Append(FLAttr);
											elem_tipo->Attributes->Append(ART_PREAttr);
											elem_tipo->Attributes->Append(PRAttr);

											//Add the node to the document.
											elem_linea->AppendChild(elem_tipo);
										}
										else
										{
											XmlNode ^ elem_opcion = opcion_comparativa[0];

											//Agregar nodo linea
											XmlAttribute ^ numeroAttrLinea = comparativa_doc->CreateAttribute("numero");
											numeroAttrLinea->Value = analisis->Attributes["numero"]->Value->ToString();
											XmlAttribute ^ textoAttrLinea = comparativa_doc->CreateAttribute("texto");
											textoAttrLinea->Value = analisis->Attributes["texto"]->Value->ToString();

											XmlElement ^ elem_linea = comparativa_doc->CreateElement( "linea" );
											elem_linea->Attributes->Append(numeroAttrLinea);
											elem_linea->Attributes->Append(textoAttrLinea);

											//Agregar nodo tipo
											XmlAttribute ^ TextoAttr = comparativa_doc->CreateAttribute("texto");
											TextoAttr->Value = texto_coincidente;
											XmlAttribute ^ FCAttr = comparativa_doc->CreateAttribute("FC");
											if (forma_canonica)
												FCAttr->Value = "true";
											else
												FCAttr->Value = "false";
											XmlAttribute ^ CGAttr = comparativa_doc->CreateAttribute("CG");
											if (categoria)
												CGAttr->Value = "true";
											else
												CGAttr->Value = "false";
											XmlAttribute ^ GNAttr = comparativa_doc->CreateAttribute("GN");
											if (gen_num)
												GNAttr->Value = "true";
											else
												GNAttr->Value = "false";
											XmlAttribute ^ FLAttr = comparativa_doc->CreateAttribute("FL");
											if (flexion)
												FLAttr->Value = "true";
											else
												FLAttr->Value = "false";
											XmlAttribute ^ ART_PREAttr = comparativa_doc->CreateAttribute("ART_PRE");
											if (art_pre)
												ART_PREAttr->Value = "true";
											else
												ART_PREAttr->Value = "false";
											XmlAttribute ^ PRAttr = comparativa_doc->CreateAttribute("PR");
											if (art_pre)
												PRAttr->Value = "true";
											else
												PRAttr->Value = "false";

											XmlElement ^ elem_tipo = comparativa_doc->CreateElement( "tipo" );
											elem_tipo->Attributes->Append(TextoAttr);
											elem_tipo->Attributes->Append(FCAttr);
											elem_tipo->Attributes->Append(CGAttr);
											elem_tipo->Attributes->Append(GNAttr);
											elem_tipo->Attributes->Append(FLAttr);
											elem_tipo->Attributes->Append(ART_PREAttr);
											elem_tipo->Attributes->Append(PRAttr);

											//Add the node to the document.
											elem_linea->AppendChild(elem_tipo);
											elem_opcion->AppendChild(elem_linea);
										}
									}
									else
									{
										XmlNode ^ elem = locucion_comparativa[0];

										//Agregar nodo opcion
										XmlAttribute ^ numeroAttr = comparativa_doc->CreateAttribute("numero");
										numeroAttr->Value = nodoLocucion->Attributes["id"]->Value->ToString();
										XmlAttribute ^ textoAttr = comparativa_doc->CreateAttribute("texto");
										textoAttr->Value = nodoLocucion->Attributes["texto"]->Value->ToString();

										XmlElement ^ elem_opcion = comparativa_doc->CreateElement( "opcion" );
										elem_opcion->Attributes->Append(numeroAttr);
										elem_opcion->Attributes->Append(textoAttr);

										//Agregar nodo linea
										XmlAttribute ^ numeroAttrLinea = comparativa_doc->CreateAttribute("numero");
										numeroAttrLinea->Value = analisis->Attributes["numero"]->Value->ToString();
										XmlAttribute ^ textoAttrLinea = comparativa_doc->CreateAttribute("texto");
										textoAttrLinea->Value = analisis->Attributes["texto"]->Value->ToString();

										XmlElement ^ elem_linea = comparativa_doc->CreateElement( "linea" );
										elem_linea->Attributes->Append(numeroAttrLinea);
										elem_linea->Attributes->Append(textoAttrLinea);

										//Agregar nodo tipo
										XmlAttribute ^ TextoAttr = comparativa_doc->CreateAttribute("texto");
										TextoAttr->Value = texto_coincidente;
										XmlAttribute ^ FCAttr = comparativa_doc->CreateAttribute("FC");
										if (forma_canonica)
											FCAttr->Value = "true";
										else
											FCAttr->Value = "false";
										XmlAttribute ^ CGAttr = comparativa_doc->CreateAttribute("CG");
										if (categoria)
											CGAttr->Value = "true";
										else
											CGAttr->Value = "false";
										XmlAttribute ^ GNAttr = comparativa_doc->CreateAttribute("GN");
										if (gen_num)
											GNAttr->Value = "true";
										else
											GNAttr->Value = "false";
										XmlAttribute ^ FLAttr = comparativa_doc->CreateAttribute("FL");
										if (flexion)
											FLAttr->Value = "true";
										else
											FLAttr->Value = "false";
										XmlAttribute ^ ART_PREAttr = comparativa_doc->CreateAttribute("ART_PRE");
										if (art_pre)
											ART_PREAttr->Value = "true";
										else
											ART_PREAttr->Value = "false";
										XmlAttribute ^ PRAttr = comparativa_doc->CreateAttribute("PR");
										if (art_pre)
											PRAttr->Value = "true";
										else
											PRAttr->Value = "false";

										XmlElement ^ elem_tipo = comparativa_doc->CreateElement( "tipo" );
										elem_tipo->Attributes->Append(TextoAttr);
										elem_tipo->Attributes->Append(FCAttr);
										elem_tipo->Attributes->Append(CGAttr);
										elem_tipo->Attributes->Append(GNAttr);
										elem_tipo->Attributes->Append(FLAttr);
										elem_tipo->Attributes->Append(ART_PREAttr);
										elem_tipo->Attributes->Append(PRAttr);

										//Add the node to the document.
										elem_linea->AppendChild(elem_tipo);
										elem_opcion->AppendChild(elem_linea);
										elem->AppendChild(elem_opcion);
									}
								}
								else
								{
									//Agregar nodo locucion
									XmlAttribute ^ IdAttr = comparativa_doc->CreateAttribute("numero");
									IdAttr->Value = nodoLocucion->Attributes["id_locucion"]->Value->ToString();

									XmlElement ^ elem = comparativa_doc->CreateElement( "locucion" );
									elem->Attributes->Append(IdAttr);

									//Agregar nodo opcion
									XmlAttribute ^ numeroAttr = comparativa_doc->CreateAttribute("numero");
									numeroAttr->Value = nodoLocucion->Attributes["id"]->Value->ToString();
									XmlAttribute ^ textoAttr = comparativa_doc->CreateAttribute("texto");
									textoAttr->Value = nodoLocucion->Attributes["texto"]->Value->ToString();

									XmlElement ^ elem_opcion = comparativa_doc->CreateElement( "opcion" );
									elem_opcion->Attributes->Append(numeroAttr);
									elem_opcion->Attributes->Append(textoAttr);

									//Agregar nodo linea
									XmlAttribute ^ numeroAttrLinea = comparativa_doc->CreateAttribute("numero");
									numeroAttrLinea->Value = analisis->Attributes["numero"]->Value->ToString();
									XmlAttribute ^ textoAttrLinea = comparativa_doc->CreateAttribute("texto");
									textoAttrLinea->Value = analisis->Attributes["texto"]->Value->ToString();

									XmlElement ^ elem_linea = comparativa_doc->CreateElement( "linea" );
									elem_linea->Attributes->Append(numeroAttrLinea);
									elem_linea->Attributes->Append(textoAttrLinea);

									//Agregar nodo tipo
									XmlAttribute ^ TextoAttr = comparativa_doc->CreateAttribute("texto");
									TextoAttr->Value = texto_coincidente;
									XmlAttribute ^ FCAttr = comparativa_doc->CreateAttribute("FC");
									if (forma_canonica)
										FCAttr->Value = "true";
									else
										FCAttr->Value = "false";
									XmlAttribute ^ CGAttr = comparativa_doc->CreateAttribute("CG");
									if (categoria)
										CGAttr->Value = "true";
									else
										CGAttr->Value = "false";
									XmlAttribute ^ GNAttr = comparativa_doc->CreateAttribute("GN");
									if (gen_num)
										GNAttr->Value = "true";
									else
										GNAttr->Value = "false";
									XmlAttribute ^ FLAttr = comparativa_doc->CreateAttribute("FL");
									if (flexion)
										FLAttr->Value = "true";
									else
										FLAttr->Value = "false";
									XmlAttribute ^ ART_PREAttr = comparativa_doc->CreateAttribute("ART_PRE");
									if (art_pre)
										ART_PREAttr->Value = "true";
									else
										ART_PREAttr->Value = "false";
									XmlAttribute ^ PRAttr = comparativa_doc->CreateAttribute("PR");
									if (art_pre)
										PRAttr->Value = "true";
									else
										PRAttr->Value = "false";

									XmlElement ^ elem_tipo = comparativa_doc->CreateElement( "tipo" );
									elem_tipo->Attributes->Append(TextoAttr);
									elem_tipo->Attributes->Append(FCAttr);
									elem_tipo->Attributes->Append(CGAttr);
									elem_tipo->Attributes->Append(GNAttr);
									elem_tipo->Attributes->Append(FLAttr);
									elem_tipo->Attributes->Append(ART_PREAttr);
									elem_tipo->Attributes->Append(PRAttr);

									//Add the node to the document.
									elem_linea->AppendChild(elem_tipo);
									elem_opcion->AppendChild(elem_linea);
									elem->AppendChild(elem_opcion);
									root->AppendChild( elem );
								}
							}
						}
					}
					catch (std::exception& ex)
					{
						throw ex;
					}
				}

				/*if (f_coincidencias != NULL)
				fclose(f_coincidencias);*/
			}
		}


		/*bool CompruebaConsecutivos(std::vector < std::vector<int> > * v_coincidencias, int indice_vector, int posicion_anterior, bool puntos_suspensivos)
		{
		for (int i = 0; i < v_coincidencias->size())

		if (indice_vector == v_coincidencias->size())
		return true;
		if ((*v_coincidencias)[indice_vector].size() == 0)
		return false;

		bool coincidencia = false;
		for(std::vector<int>::iterator i = (*v_coincidencias)[indice_vector].begin(); i != (*v_coincidencias)[indice_vector].end(); *i++)
		{
		int elem = *i;
		if ((posicion_anterior == 0
		|| (elem == posicion_anterior + 1 && !puntos_suspensivos)
		|| (elem <= (posicion_anterior + MAX_SUSPENSIVOS + 1) && puntos_suspensivos))					
		&& elem > posicion_anterior)
		{
		if (CompruebaConsecutivos(v_coincidencias, indice_vector + 1, elem, puntos_suspensivos))
		coincidencia = true;
		}
		}

		return coincidencia;
		}*/

		//---------------------------------------------------------------------------
		void ObtieneCategoriasYFlexiones()
		{
			//Se abre el fichero en modo lectura
			StreamReader ^ fd = gcnew StreamReader(f_categorias, System::Text::Encoding::Default);
			String ^ texto;

			for(int i = 0; i < 9; i++)
			{
				std::vector<int> vector;
				v_categorias.push_back(vector);
			}

			for(int i = 0; i < 6; i++)
			{
				std::vector<int> vector;
				v_flexiones.push_back(vector);
			}

			//mientras no se alcance el final del fichero
			while (texto = fd->ReadLine())
			{
				int indice = texto->IndexOf(";");
				String ^ categoria;

				if (indice > 0)
					categoria = texto->Substring(0, indice);
				else 
					continue;

				int valor = Convert::ToInt32(categoria) - 6000;
				//ADJETIVO
				if (texto->Contains("adjetivo"))//107
					v_categorias[0].push_back(valor);
				//ADVERBIO
				if (texto->Contains("adverbio"))//107
					v_categorias[1].push_back(valor);
				//ARTÍCULO
				if (texto->Contains("artículo"))//3
					v_categorias[2].push_back(valor);
				//NOMBRE PROPIO
				if (texto->Contains("nombre propio"))//17
					v_categorias[3].push_back(valor);
				//NUMERAL
				if (texto->Contains("numeral"))//5
					v_categorias[4].push_back(valor);
				//PREPOSICIÓN
				if (texto->Contains("preposición"))//14
					v_categorias[5].push_back(valor);
				//PRONOMBRE
				if (texto->Contains("pronombre"))//37
				{
					v_categorias[6].push_back(valor);
					if (texto->Contains("pronombre personal"))
						v_pron_personal.push_back(valor);
				}
				//SUSTANTIVO
				if (texto->Contains("sustantivo"))//155
					v_categorias[7].push_back(valor);
				//VERBO
				if (texto->Contains("verbo"))//58
					v_categorias[8].push_back(valor);
			}

			fd->Close();

			fd = gcnew StreamReader(f_flexiones);
			//mientras no se alcance el final del fichero
			while (texto = fd->ReadLine())
			{
				int indice = texto->IndexOf(":");
				String ^ flexion;

				if (indice > 0)
					flexion = texto->Substring(0, indice);
				else 
					continue;

				int valor = Convert::ToInt32(flexion);
				//INDICATIVO
				if (texto->Contains("indicativo"))//24 * 58 = 1392
					v_flexiones[0].push_back(valor);
				//IMPERATIVO
				if (texto->Contains("imperativo"))//6 * 58 = 348
					v_flexiones[1].push_back(valor);
				//PARTICIPIO
				if (texto->Contains("participio"))//6 * 58 = 348
					v_flexiones[2].push_back(valor);
				//SUBJUNTIVO
				if (texto->Contains("subjuntivo"))//18 * 58 = 1044
					v_flexiones[3].push_back(valor);
				//IMPERFECTO DE SUBJUNTIVO
				if (texto->Contains("imperfecto de subjuntivo"))//12 * 58 = 696
					v_flexiones[4].push_back(valor);
			}

			fd->Close();
		}

		void ObtieneComparativa(String ^ fichero)
		{
			String ^ fichero_resultados = fichero;
			String ^ fichero_resultados_varela;

			int indice = fichero_resultados->IndexOf(".txt");
			if (indice != -1)
			{
				fichero_resultados = fichero_resultados->Substring(0, indice);
				fichero_resultados_varela = f_comparativa_varela + fichero_resultados + ".xml";
				fichero_resultados = f_comparativa + fichero_resultados + ".xml";
			}

			FileStream ^ f_xml = File::Create(fichero_resultados);
			Encoding ^ linea = Encoding::Default;

			String ^ linea_fichero = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
			int len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

			linea_fichero = "<resultado>\n";
			len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0,  len);

			linea_fichero = "</resultado>\n";
			len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0,  len);

			f_xml->Close();

			f_xml = File::Create(fichero_resultados_varela);
			linea = Encoding::Default;

			linea_fichero = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
			len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

			linea_fichero = "<resultado>\n";
			len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0,  len);

			linea_fichero = "</resultado>\n";
			len = linea_fichero->Length;
			f_xml->Write(linea->GetBytes(linea_fichero), 0,  len);

			f_xml->Close();

			XmlDocument ^ xmldoc = gcnew XmlDocument();
			xmldoc->Load(fichero_resultados);
			XmlDocument ^ xmldoc_varela = gcnew XmlDocument();
			xmldoc_varela->Load(fichero_resultados_varela);

			forma_canonica = true;
			categoria = true;
			flexion = true;
			gen_num = true;
			pronombre = true;
			art_pre = false;

			if (!AnalizaFicheros(fichero))
			{
				MessageBox::Show("No ha sido posible analizar el fichero indicado");
				return;
			}

			//Forma canónica y Categoría gramatical
			forma_canonica = true;
			categoria = true;
			pronombre = false;
			art_pre = false;
			gen_num = false;
			flexion = false;

			BuscaCoincidencias(fichero, f_res_base, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base, xmldoc_varela);

			//Forma canónica, Categoría gramatical, Género y Número
			gen_num = true;

			BuscaCoincidencias(fichero, f_res_base, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base, xmldoc_varela);

			//Forma canónica, Categoría gramatical y Flexión
			gen_num = false;
			flexion = true;

			BuscaCoincidencias(fichero, f_res_base, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base, xmldoc_varela);

			//Forma canónica, Categoría gramatical, Género, Número y Flexión
			gen_num = true;

			BuscaCoincidencias(fichero, f_res_base, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base, xmldoc_varela);

			//Forma canónica, Categoría gramatical y Pronombres
			pronombre = true;
			gen_num = false;
			flexion = false;

			BuscaCoincidencias(fichero, f_res_base, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base, xmldoc_varela);

			//Forma canónica, Categoría gramatical, Género, Número y Pronombres
			gen_num = true;

			BuscaCoincidencias(fichero, f_res_base, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base, xmldoc_varela);

			//Forma canónica, Categoría gramatical, Flexión y Pronombres
			gen_num = false;
			flexion = true;

			BuscaCoincidencias(fichero, f_res_base, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base, xmldoc_varela);

			//Forma canónica, Categoría gramatical, Género, Número, Flexión y Pronombres
			gen_num = true;

			BuscaCoincidencias(fichero, f_res_base, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base, xmldoc_varela);

			forma_canonica = true;
			categoria = true;
			flexion = true;
			gen_num = true;
			pronombre = true;
			art_pre = true;

			if (!AnalizaFicheros(fichero))
			{
			MessageBox::Show("No ha sido posible analizar el fichero indicado");
			return;
			}

			//Forma canónica y Categoría gramatical
			forma_canonica = true;
			categoria = true;
			pronombre = false;
			gen_num = false;
			flexion = false;

			BuscaCoincidencias(fichero, f_res_base_art_pre, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base_art_pre, xmldoc_varela);

			//Forma canónica, Categoría gramatical, Género y Número
			gen_num = true;

			BuscaCoincidencias(fichero, f_res_base_art_pre, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base_art_pre, xmldoc_varela);

			//Forma canónica, Categoría gramatical y Flexión
			gen_num = false;
			flexion = true;

			BuscaCoincidencias(fichero, f_res_base_art_pre, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base_art_pre, xmldoc_varela);

			//Forma canónica, Categoría gramatical, Género, Número y Flexión
			gen_num = true;

			BuscaCoincidencias(fichero, f_res_base_art_pre, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base_art_pre, xmldoc_varela);

			//Forma canónica, Categoría gramatical y Pronombres
			pronombre = true;
			gen_num = false;
			flexion = false;

			BuscaCoincidencias(fichero, f_res_base_art_pre, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base_art_pre, xmldoc_varela);

			//Forma canónica, Categoría gramatical, Género, Número y Pronombres
			gen_num = true;

			BuscaCoincidencias(fichero, f_res_base_art_pre, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base_art_pre, xmldoc_varela);

			//Forma canónica, Categoría gramatical, Flexión y Pronombres
			gen_num = false;
			flexion = true;

			BuscaCoincidencias(fichero, f_res_base_art_pre, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base_art_pre, xmldoc_varela);

			//Forma canónica, Categoría gramatical, Género, Número, Flexión y Pronombres
			gen_num = true;

			BuscaCoincidencias(fichero, f_res_base_art_pre, xmldoc);
			BuscaCoincidencias(fichero, f_res_varela_base_art_pre, xmldoc_varela);

			XPathNavigator ^ navigator = xmldoc->CreateNavigator();
			XPathExpression ^ selectExpression = navigator->Compile("/resultado/locucion");
			selectExpression->AddSort("@numero", XmlSortOrder::Ascending, XmlCaseOrder::None, "", XmlDataType::Number);			
			XPathNodeIterator ^ nodeIterator = navigator->Select(selectExpression);

			xmldoc->Load(fichero_resultados);
			XmlNode^ root = xmldoc->DocumentElement;

			while (nodeIterator->MoveNext())
			root->AppendChild(((IHasXmlNode^)nodeIterator->Current)->GetNode());			 

			navigator = xmldoc_varela->CreateNavigator();	
			selectExpression = navigator->Compile("/resultado/locucion");
			selectExpression->AddSort("@numero", XmlSortOrder::Ascending, XmlCaseOrder::None, "", XmlDataType::Number);			
			nodeIterator = navigator->Select(selectExpression);	

			xmldoc_varela->Load(fichero_resultados_varela);
			root = xmldoc_varela->DocumentElement;

			while (nodeIterator->MoveNext())
				root->AppendChild(((IHasXmlNode^)nodeIterator->Current)->GetNode());

			xmldoc->Save(fichero_resultados);
			xmldoc_varela->Save(fichero_resultados_varela);
		}



#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
			 {

				 art_pre = ART_PRE_CB->Checked;
				 forma_canonica = FC_CB->Checked;
				 categoria = CAT_CB->Checked;
				 flexion = FLEX_CB->Checked;
				 gen_num = GEN_NUM_CB->Checked;

				 forma_canonica = true;
				 categoria = true;
				 flexion = true;
				 gen_num = true;
				 pronombre = true;

				 ObtieneCategoriasYFlexiones();
				 inicializaMorfo("..\\Datos\\In\\datosini\\");

				 FileStream ^ no_reconocidas = File::Create(f_no_rec);

				 art_pre = false;
				 AnalizaLocuciones(no_reconocidas);
				 AnalizaLocucionesVarela(no_reconocidas);

				 art_pre = true;
				 AnalizaLocuciones(no_reconocidas);
				 AnalizaLocucionesVarela(no_reconocidas);

				 no_reconocidas->Close();

				 System::TimeSpan tiempo_inicio = DateTime::Now.TimeOfDay; 

				 //ObtieneComparativa(Fichero_TB->Text);
				 ObtieneComparativa("Prueba.txt");
				 //ObtieneComparativa("ejemplos.txt");
				 //ObtieneComparativa("Autentico amor.txt");
				 //ObtieneComparativa("Armagedon.txt");
				 //ObtieneComparativa("48 sonetos de amor.txt");
				 //ObtieneComparativa("Aurora.txt");
				 //ObtieneComparativa("Alien 3.txt");

				 FileStream ^ f_xml = File::Create("..\\Datos\\Out\\estadisticas.xml");
				 Encoding ^ linea = Encoding::Default;

				 String ^ linea_fichero = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
				 int len = linea_fichero->Length;
				 f_xml->Write(linea->GetBytes(linea_fichero), 0, len);

				 linea_fichero = "<resultado>\n";
				 len = linea_fichero->Length;
				 f_xml->Write(linea->GetBytes(linea_fichero), 0,  len);

				 linea_fichero = "</resultado>\n";
				 len = linea_fichero->Length;
				 f_xml->Write(linea->GetBytes(linea_fichero), 0,  len);

				 f_xml->Close();

				 XmlDocument ^ xmldoc = gcnew XmlDocument();
				 xmldoc->Load("..\\Datos\\Out\\estadisticas.xml");

				 /*ObtieneEstadisticas(xmldoc, "..\\Datos\\Out\\comparativa_varela_Autentico amor.xml");
				 ObtieneEstadisticas(xmldoc, "..\\Datos\\Out\\comparativa_Autentico amor.xml");				 
				 ObtieneEstadisticas(xmldoc, "..\\Datos\\Out\\comparativa_varela_Armagedon.xml");
				 ObtieneEstadisticas(xmldoc, "..\\Datos\\Out\\comparativa_Armagedon.xml");
				 ObtieneEstadisticas(xmldoc, "..\\Datos\\Out\\comparativa_varela_48 sonetos de amor.xml");
				 ObtieneEstadisticas(xmldoc, "..\\Datos\\Out\\comparativa_48 sonetos de amor.xml");*/
				 ObtieneEstadisticas(xmldoc, "..\\Datos\\Out\\comparativa_varela_Prueba.xml");
				 ObtieneEstadisticas(xmldoc, "..\\Datos\\Out\\comparativa_Prueba.xml");	
				 xmldoc->Save("..\\Datos\\Out\\estadisticas.xml");

				 System::TimeSpan tiempo_fin = DateTime::Now.TimeOfDay;
				 tiempo_fin = tiempo_fin - tiempo_inicio;
				 MessageBox::Show(tiempo_fin.Hours.ToString() + " h " +
					 tiempo_fin.Minutes.ToString() + " min " +
					 tiempo_fin.Seconds.ToString() + " segs " +
					 tiempo_fin.Milliseconds.ToString() + " ms");

				 this->Close();
			 }



	};
}

