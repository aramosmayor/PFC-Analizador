// Analizador.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include "Form1.h"

using namespace Analizador;
using namespace System::Data::OleDb;
using namespace System::Data::Common;
using namespace System::Runtime::InteropServices; 
using namespace System::Text;
using namespace System::Xml;
using namespace System::Xml::XPath;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Habilitar los efectos visuales de Windows XP antes de crear ningún control
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Crear la ventana principal y ejecutarla
	Application::Run(gcnew Form1());
	return 0;
}
