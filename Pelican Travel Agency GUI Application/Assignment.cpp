//Student Name: Caleb Ellis
//Student ID: 400014224

//Step 1: Include Header File
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    # include <wx/wx.h>
    # include <wx/spinctrl.h>
    # include <wx/textctrl.h>
    # include <wx/combobox.h>
#endif

using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "DataDialog.h"
#include "BSTree.h"
#include "AVLTree.h"
#include "RBTree.h"
#include "SplayTree.h"
#include "Set.h"
/*#include "MinHeap.h"
#include "MaxHeap.h"*/

//Create Global Variables for ADTs
BSTree* bstree = new BSTree();
AVLTree* avlTree = new AVLTree();
RBTree* rbTree = new RBTree();
SplayTree* splayTree = new SplayTree();
Set* setA = new Set();
Set* setB = new Set();
Set* intersectionSet = new Set(); //Intersection Set
Set* unionSet = new Set(); //Union Set
/*MinHeap* minHeap = new MinHeap();
MaxHeap* maxHeap = new MaxHeap();*/

struct clientRecord
{
    int clientID;
    char firstName[20];
    char lastName[20];
    char destination[20];
    char payment[15];
    char booking[15];
};

typedef struct clientRecord record;

//Step Two: Create an Inherited Application Class from wxApp and Declare a Function to Execute The Program
class ProjectAssignment : public wxApp {
    public:
        virtual bool OnInit(); //This is used for the Application Startup
};

//Step Three:
class AssignmentFrame : public wxFrame {
    private:
        DECLARE_EVENT_TABLE() //This Handles Events
    public:
        AssignmentFrame(const wxString& title, const wxPoint& pos, const wxSize& size); //This is the Contructor

        //Event Handlers Go Here(If I Had Any)
        void onOpenFile (wxCommandEvent& event);
        void onSaveFile (wxCommandEvent& event);
        void onSaveAsFile (wxCommandEvent& event);
        void onExitFile (wxCommandEvent& event);
        void onDisplayFile (wxCommandEvent& event);

        void onCreateADTs (wxCommandEvent& event);
        void onAddRecord (wxCommandEvent& WXUNUSED(event));
        //void onAddRecord (wxCommandEvent& event);
        void onDeleteRecord (wxCommandEvent& WXUNUSED(event));
        //void onDeleteRecord (wxCommandEvent& event);
        void onBSTInorder (wxCommandEvent& event);
        void onBSTPreorder (wxCommandEvent& event);
        void onBSTPostorder (wxCommandEvent& event);

        void onAVLInorder (wxCommandEvent& event);
        void onAVLPreorder (wxCommandEvent& event);
        void onAVLPostorder (wxCommandEvent& event);

        void onRBInorder (wxCommandEvent& event);
        void onRBPreorder (wxCommandEvent& event);
        void onRBPostorder (wxCommandEvent& event);

        void onSplayInorder (wxCommandEvent& event);
        void onSplayPreorder (wxCommandEvent& event);
        void onSplayPostorder (wxCommandEvent& event);

        void onDisplayAllMinHeap (wxCommandEvent& event);
        void onHeapSortMinHeap (wxCommandEvent& event);

        void onDisplayAllMaxHeap (wxCommandEvent& event);
        void onHeapSortMaxHeap (wxCommandEvent& event);

        void onDisplaySetA (wxCommandEvent& event);
        void onDisplaySetB (wxCommandEvent& event);
        void onDisplayIntersection (wxCommandEvent& event);
        void onDisplayUnion (wxCommandEvent& event);

        void onAboutHelp (wxCommandEvent& event);
        void onExitHelp (wxCommandEvent& event);

        //void getData(wxCommandEvent& WXUNUSED(event));

        //Public attributes - New added stuff
        wxTextCtrl* MainEditBox;
        wxTextCtrl* filenameTextBox;
        wxString CurrentDocPath; // The Path to the file we have open
};

//Step Four: Declare the Compiler Directives
DECLARE_APP(ProjectAssignment) //Declare Application Class
IMPLEMENT_APP(ProjectAssignment) //Create Application Class Object

//The Enumeration Table Goes Here!
enum {
    ID_OpenFile = wxID_HIGHEST + 1,
    ID_SaveFile,
    ID_SaveAsFile,
    ID_ExitFile,

    ID_CreateADTs,
    ID_AddRecord,
    ID_DeleteRecord,

    ID_BSTInorder,
    ID_BSTPreorder,
    ID_BSTPostorder,

    ID_AVLInorder,
    ID_AVLPreorder,
    ID_AVLPostorder,

    ID_RBInorder,
    ID_RBPreorder,
    ID_RBPostorder,

    ID_SplayInorder,
    ID_SplayPreorder,
    ID_SplayPostorder,

    ID_DisplayAllMinHeap,
    ID_HeapSortMinHeap,

    ID_DisplayAllMaxHeap,
    ID_HeapSortMaxHeap,

    ID_DisplaySetA,
    ID_DisplaySetB,
    ID_DisplayIntersection,
    ID_DisplayUnion,

    ID_DisplayFile,

    ID_AboutHelp,
    ID_ExitHelp,

    //ID_GetData,
};

//Step Five: Define The Event Table
BEGIN_EVENT_TABLE (AssignmentFrame, wxFrame)
    EVT_MENU(ID_OpenFile, AssignmentFrame::onOpenFile)
    EVT_MENU(ID_SaveFile, AssignmentFrame::onSaveFile)
    EVT_MENU(ID_SaveAsFile, AssignmentFrame::onSaveAsFile)
    EVT_MENU(ID_ExitFile, AssignmentFrame::onExitFile)
    EVT_MENU(ID_DisplayFile, AssignmentFrame::onDisplayFile)

    EVT_MENU(ID_CreateADTs, AssignmentFrame::onCreateADTs)
    EVT_MENU(ID_AddRecord, AssignmentFrame::onAddRecord)
    EVT_MENU(ID_DeleteRecord, AssignmentFrame::onDeleteRecord)

    EVT_MENU(ID_BSTInorder, AssignmentFrame::onBSTInorder)
    EVT_MENU(ID_BSTPreorder, AssignmentFrame::onBSTPreorder)
    EVT_MENU(ID_BSTPostorder, AssignmentFrame::onBSTPostorder)

    EVT_MENU(ID_AVLInorder, AssignmentFrame::onAVLInorder)
    EVT_MENU(ID_AVLPreorder, AssignmentFrame::onAVLPreorder)
    EVT_MENU(ID_AVLPostorder, AssignmentFrame::onAVLPostorder)

    EVT_MENU(ID_RBInorder, AssignmentFrame::onRBInorder)
    EVT_MENU(ID_RBPreorder, AssignmentFrame::onRBPreorder)
    EVT_MENU(ID_RBPostorder, AssignmentFrame::onRBPostorder)

    EVT_MENU(ID_SplayInorder, AssignmentFrame::onSplayInorder)
    EVT_MENU(ID_SplayPreorder, AssignmentFrame::onSplayPreorder)
    EVT_MENU(ID_SplayPostorder, AssignmentFrame::onSplayPostorder)

    EVT_MENU(ID_DisplayAllMinHeap, AssignmentFrame::onDisplayAllMinHeap)
    EVT_MENU(ID_HeapSortMinHeap, AssignmentFrame::onHeapSortMinHeap)

    EVT_MENU(ID_DisplayAllMaxHeap, AssignmentFrame::onDisplayAllMaxHeap)
    EVT_MENU(ID_HeapSortMaxHeap, AssignmentFrame::onHeapSortMaxHeap)

    EVT_MENU(ID_DisplaySetA, AssignmentFrame::onDisplaySetA)
    EVT_MENU(ID_DisplaySetB, AssignmentFrame::onDisplaySetB)
    EVT_MENU(ID_DisplayIntersection, AssignmentFrame::onDisplayIntersection)
    EVT_MENU(ID_DisplayUnion, AssignmentFrame::onDisplayUnion)

    EVT_MENU(ID_AboutHelp, AssignmentFrame::onAboutHelp)
    EVT_MENU(ID_ExitHelp, AssignmentFrame::onExitHelp)

    //EVT_MENU(ID_GetData, AssignmentFrame::getData)
END_EVENT_TABLE()

//Step Six: Define the Application Class Function
bool ProjectAssignment::OnInit() {
    //Create the Main Application Window
    AssignmentFrame *frame = new AssignmentFrame(wxT("COMP 2611 - Pelican Travels Database"), wxPoint(50,50), wxSize(800,700));

    frame -> Show(true); //Display The Application Window

    return true; //Start the Event Loop
}

//Step Seven: Define the Frame Class' Constructor Functions
AssignmentFrame::AssignmentFrame (const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame((wxFrame *)NULL, -1, title, pos, size) {
    //Set the Frame Icon
    SetIcon(wxIcon(wxT("UWILogo.xpm")));

    //Create Menu Items for Menu Bar
    wxMenu *fileMenu = new wxMenu;
    wxMenu *editMenu = new wxMenu;
    wxMenu *bstMenu = new wxMenu;
    wxMenu *avlMenu = new wxMenu;
    wxMenu *rbMenu = new wxMenu;
    wxMenu *splayMenu = new wxMenu;
    wxMenu *minHeapMenu = new wxMenu;
    wxMenu *maxHeapMenu = new wxMenu;
    wxMenu *setMenu = new wxMenu;
    wxMenu *helpMenu = new wxMenu;

    //Append Sub-Menu Items to File Menu
    fileMenu->Append(ID_OpenFile, wxT("Open"), wxT("Open a File"));
    fileMenu->Append(ID_SaveFile, wxT("Save"), wxT("Saves the File"));
    fileMenu->Append(ID_SaveAsFile, wxT("Save As"), wxT("Saves the File as Another Name or Type"));
    fileMenu->Append(ID_ExitFile, wxT("Exit"), wxT("Quit this program"));
    fileMenu->Append(ID_DisplayFile, wxT("Display File"), wxT("Display a File"));

    //Append Sub-Menu Items to the Edit Menu
    editMenu->Append(ID_CreateADTs, wxT("Create ADTs"), wxT(""));
    editMenu->Append(ID_AddRecord, wxT("Add Record"), wxT(""));;
    editMenu->Append(ID_DeleteRecord, wxT("Delete Record"), wxT(""));

    //Append Sub-Menu Items to the BST Menu
    bstMenu->Append(ID_BSTInorder, wxT("Inorder"), wxT(""));
    bstMenu->Append(ID_BSTPreorder, wxT("Preorder"), wxT(""));
    bstMenu->Append(ID_BSTPostorder, wxT("Postorder"), wxT(""));

    //Append Sub-Menu Items to the AVL Menu
    avlMenu->Append(ID_AVLInorder, wxT("Inorder"), wxT(""));
    avlMenu->Append(ID_AVLPreorder, wxT("Preorder"), wxT(""));
    avlMenu->Append(ID_AVLPostorder, wxT("Postorder"), wxT(""));

    //Append Sub-Menu Items to the RB Menu
    rbMenu->Append(ID_RBInorder, wxT("Inorder"), wxT(""));
    rbMenu->Append(ID_RBPreorder, wxT("Preorder"), wxT(""));
    rbMenu->Append(ID_RBPostorder, wxT("Postorder"), wxT(""));

    //Append Sub-Menu Items to the Splay Tree Menu
    splayMenu->Append(ID_SplayInorder, wxT("Inorder"), wxT(""));
    splayMenu->Append(ID_SplayPreorder, wxT("Preorder"), wxT(""));
    splayMenu->Append(ID_SplayPostorder, wxT("Postorder"), wxT(""));

    //Append Sub-Menu Items to the Min Heap Menu
    minHeapMenu->Append(ID_DisplayAllMinHeap, wxT("Display All"), wxT(""));
    minHeapMenu->Append(ID_HeapSortMinHeap, wxT("Heap Sort"), wxT(""));

    //Append Sub-Menu Items to the Max Heap Menu
    maxHeapMenu->Append(ID_DisplayAllMaxHeap, wxT("Display All"), wxT(""));
    maxHeapMenu->Append(ID_HeapSortMaxHeap, wxT("Heap Sort"), wxT(""));

    //Append Sub-Menu Items to the Set Menu
    setMenu->Append(ID_DisplaySetA, wxT("Display SetA"), wxT(""));
    setMenu->Append(ID_DisplaySetB, wxT("Display SetB"), wxT(""));
    setMenu->Append(ID_DisplayIntersection, wxT("Display Intersection"), wxT(""));
    setMenu->Append(ID_DisplayUnion, wxT("Display Union"), wxT(""));

    //Append Sub-Menu Items to Help Menu
    helpMenu->Append(ID_AboutHelp, wxT("About"), wxT("Show About dialog"));
    helpMenu->Append(ID_ExitHelp, wxT("Exit"), wxT("Quit the Program"));

    //Append Menu Items to Menu Bar
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar -> Append(fileMenu, wxT("File"));
    menuBar -> Append(editMenu, wxT("Edit"));
    menuBar -> Append(bstMenu, wxT("BST"));
    menuBar -> Append(avlMenu, wxT("AVL Tree"));
    menuBar -> Append(rbMenu, wxT("RB Tree"));
    menuBar -> Append(splayMenu, wxT("Splay Tree"));
    menuBar -> Append(minHeapMenu, wxT("Min Heap"));
    menuBar -> Append(maxHeapMenu, wxT("Max Heap"));
    menuBar -> Append(setMenu, wxT("Set"));
    menuBar -> Append(helpMenu, wxT("Help"));

    //Attach Menu Bar to Frame
    SetMenuBar(menuBar);

    //Create Status menuBar
    CreateStatusBar(3);

    SetStatusText(wxT("Ready..."), 0);
    SetStatusText(wxT("Caleb Ellis"), 1);
    SetStatusText(wxT("400014224"), 2);

    //Set up the panel for data display - Add to the bottom of the constructor function
//===============================================================================
//================= DO NOT CHANGE THE CODE IN THIS SECTION ======================
//===============================================================================

    wxPanel     *panel     = new wxPanel(this, -1);
    wxBoxSizer  *vbox      = new wxBoxSizer(wxVERTICAL);        //Vertical sizer for main window
    wxBoxSizer  *hbox1     = new wxBoxSizer(wxHORIZONTAL);        //Horizontal sizer for main window

    //Add two textboxes to the panel for data display
    wxBoxSizer  *hbox2     = new wxBoxSizer(wxHORIZONTAL);        //Horizontal sizer for filename window
    wxBoxSizer  *hbox3     = new wxBoxSizer(wxHORIZONTAL);        //Horizontal sizer for display window

    wxStaticText *fileLabel     = new wxStaticText(panel, wxID_ANY, wxT("File Name"));
    wxStaticText *displayLabel     = new wxStaticText(panel, wxID_ANY, wxT("Display"));

    //Initialize the filename textbox window
    filenameTextBox = new wxTextCtrl(panel, wxID_ANY, wxT("No File Opened Yet..."));

    //Initialize the display window
    MainEditBox = new wxTextCtrl(panel, wxID_ANY, wxT("No Data Available Yet..."),
                      wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE | wxTE_RICH);


    //Position the labels and textboxes in the panel
    hbox1->Add(fileLabel, 0, wxRIGHT, 8);
    hbox1->Add(filenameTextBox, 1);
    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    vbox->Add(-1, 10);
    hbox2->Add(displayLabel, 0);
    vbox->Add(hbox2, 0, wxLEFT | wxTOP, 10);
    vbox->Add(-1, 10);

    hbox3->Add(MainEditBox, 1, wxEXPAND);
    vbox->Add(hbox3, 1, wxLEFT | wxRIGHT | wxEXPAND, 10);

    vbox->Add(-1, 25);
    panel->SetSizer(vbox);

    Centre();
}

//Step Eight: Define the Frame Class' Member Functions
//=========================================================================
//==================== Definition for the File Functions ==================
//=========================================================================
void AssignmentFrame::onOpenFile(wxCommandEvent& event)
{
        // Creates a "open file" dialog with 3 file types
        wxFileDialog *OpenDialog = new wxFileDialog( this,
        (wxT("Choose a file to open")), wxEmptyString, wxEmptyString,
            (wxT("Data Files (*.dat)|*.dat|Text files (*.txt)|*.txt|All files (*.*)|*.*")), wxFD_OPEN, wxDefaultPosition);

    if (OpenDialog->ShowModal() == wxID_OK)    // if the user click "Open" instead of "cancel"
    {
        // Sets our current document to the file the user selected
        CurrentDocPath = OpenDialog->GetPath();

        //Clean up filename textbox and Display file name in filename textbox
        filenameTextBox->Clear();
        filenameTextBox->AppendText(CurrentDocPath);

        //Downgrades wxWidgets string to normal string and assign file to var
        ifstream infile(CurrentDocPath.mb_str(), ios::in | ios::binary);

        record readRecord;
        string allRecords;

        while(!infile.eof())
        {
            infile.read(reinterpret_cast<char*>(&readRecord),sizeof(record));

            allRecords.append(to_string(readRecord.clientID));
            allRecords.append("\t");
            allRecords.append(readRecord.firstName);
            allRecords.append("\t");
            allRecords.append(readRecord.lastName);
            allRecords.append("\t");
            allRecords.append(readRecord.destination);
            allRecords.append("\t");
            allRecords.append(readRecord.payment);
            allRecords.append("\t");
            allRecords.append(readRecord.booking);
            allRecords.append("\n");

            if (std::string(readRecord.payment) == "MasterCard")
            {
                bstree->recursiveInsert(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);
            }

            if (std::string(readRecord.payment) == "Diner")
            {
                avlTree->recursiveInsert(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);
            }

            if (std::string(readRecord.payment) == "Visa")
            {
                rbTree->insert(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);
            }

            if (std::string(readRecord.payment) == "Amex")
            {
                splayTree->recursiveInsert(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);
            }

            if (std::string(readRecord.booking) == "Internet")
            {
                setA->addElement(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);
            }
            if (std::string(readRecord.booking) == "Walk-in")
            {
                setB->addElement(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);
            }

            //minHeap->recursiveInsert(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);

            //maxHeap->recursiveInsert(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);*/
        }

        //Convert string var into wxWidgets String
        wxString wxRecords(allRecords.c_str(), wxConvUTF8);

        //Clear Main Text Box
        MainEditBox->Clear();
        MainEditBox->AppendText(wxT("\n All Records in File: \n\n\t"));

        MainEditBox->AppendText(allRecords);   //Displays the Records in the MainEditBox

        // Set the Title
        SetTitle(wxString(wxT("COMP 2611 - Pelican Travels Database")));
    }
}

void AssignmentFrame::onSaveFile(wxCommandEvent& event)
{
    // Save to the already-set path for the document
    MainEditBox->SaveFile(CurrentDocPath);
}

void AssignmentFrame::onSaveAsFile(wxCommandEvent& event)
{
    wxFileDialog *SaveDialog = new wxFileDialog(this, (wxT("Save File As...?")),
                        wxEmptyString, wxEmptyString,
                        (wxT("Data Files (*.dat)|*.dat|Text files (*.txt)|*.txt")),
                        wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

    // Creates a Save Dialog with 4 file types
    if (SaveDialog->ShowModal() == wxID_OK)     // If the user clicked "OK"
        {
            CurrentDocPath = SaveDialog->GetPath();

            // set the path of our current document to the file the user chose to save under
            MainEditBox->SaveFile(CurrentDocPath); // Save the file to the selected path

            // Set the Title to reflect the file open
            SetTitle(wxString(wxT("COMP2611 - Data Structures : 400014224")));
    }

}

void AssignmentFrame::onExitFile(wxCommandEvent& event)
{
    wxMessageBox(wxT("Good-bye!"), wxT("Exit"), wxOK | wxICON_INFORMATION, this);
    Close(TRUE); // Close the window
}

void AssignmentFrame::onDisplayFile(wxCommandEvent& event)
{
    filenameTextBox->Clear();
    filenameTextBox->AppendText(CurrentDocPath);

    ifstream infile(CurrentDocPath.mb_str(), ios::in | ios::binary);

    record readRecord;
    string allRecords;

    while(!infile.eof())
    {
        infile.read(reinterpret_cast<char*>(&readRecord),sizeof(record));

        allRecords.append(to_string(readRecord.clientID));
        allRecords.append("\t");
        allRecords.append(readRecord.firstName);
        allRecords.append("\t");
        allRecords.append(readRecord.lastName);
        allRecords.append("\t");
        allRecords.append(readRecord.destination);
        allRecords.append("\t");
        allRecords.append(readRecord.payment);
        allRecords.append("\t");
        allRecords.append(readRecord.booking);
        allRecords.append("\n");
    }
    //Convert string var into wxWidgets String
    wxString wxRecords(allRecords.c_str(), wxConvUTF8);

    //Clear Main Text Box
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n All Records in File: \n\n\t"));

    MainEditBox->AppendText(allRecords);   //Displays the Records in the MainEditBox

    // Set the Title
    SetTitle(wxString(wxT("COMP 2611 - Pelican Travels Database")));
}
//==========================================================================
//================== Definition for the Edit Functions =====================
//==========================================================================
void AssignmentFrame::onCreateADTs (wxCommandEvent& event)
{
    ifstream infile(CurrentDocPath.mb_str(), ios::in | ios::binary);

    record readRecord;
    string allRecords;

    bstree = new BSTree();
    avlTree = new AVLTree();
    rbTree = new RBTree();
    splayTree = new SplayTree();
    setA = new Set();
    setB = new Set();


    while(!infile.eof())
    {
        infile.read(reinterpret_cast<char*>(&readRecord),sizeof(record));

        allRecords.append(to_string(readRecord.clientID));
        allRecords.append("\t");
        allRecords.append(readRecord.firstName);
        allRecords.append("\t");
        allRecords.append(readRecord.lastName);
        allRecords.append("\t");
        allRecords.append(readRecord.destination);
        allRecords.append("\t");
        allRecords.append(readRecord.payment);
        allRecords.append("\t");
        allRecords.append(readRecord.booking);
        allRecords.append("\n");

        if (std::string(readRecord.payment) == "MasterCard")
        {
            bstree->recursiveInsert(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);
        }

        if (std::string(readRecord.payment) == "Diner")
        {
            avlTree->recursiveInsert(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);
        }

        if (std::string(readRecord.payment) == "Visa")
        {
            rbTree->insert(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);
        }

        if (std::string(readRecord.payment) == "Amex")
        {
            splayTree->recursiveInsert(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);
        }

        if (std::string(readRecord.booking) == "Internet")
        {
            setA->addElement(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);
        }
        if (std::string(readRecord.booking) == "Walk-in")
        {
            setB->addElement(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);
        }

        //minHeap->recursiveInsert(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);

        //maxHeap->recursiveInsert(readRecord.clientID, readRecord.firstName, readRecord.lastName, readRecord.destination, readRecord.payment, readRecord.booking);*/
    }

    //Clear Main Text Box
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n ADTs Were Created: \n\t"));
    MainEditBox->AppendText(wxT("\n All Records in File: \n\n\t"));

    MainEditBox->AppendText(allRecords);   //Displays the Records in the MainEditBox

    // Set the Title
    SetTitle(wxString(wxT("COMP 2611 - Pelican Travels Database")));
}

//void AssignmentFrame::onAddRecord (wxCommandEvent& event)
void AssignmentFrame::onAddRecord (wxCommandEvent& WXUNUSED(event))
{
	struct data dataRec;

	DataDialog *datadialog = new DataDialog( wxT("Pelican Travels - Data Entry"),
							wxPoint(200,200), wxSize(500,300) );

	if (datadialog->ShowModal() == wxID_OK )
	{
        //Grab value from the NameBox.
        dataRec.firstName = datadialog->firstNameEditBox->GetValue();

        //Grab value from the SurnameBox
        dataRec.lastName = datadialog->lastNameEditBox->GetValue();

        //Grab value from the DestinationBox
        dataRec.destination = datadialog->destinationEditBox->GetValue();

        //Grab value from the IDNoBox
        dataRec.clientID = datadialog->clientIDEditBox->GetValue();

        //Grab the list item selected - Payment Combo Box
        dataRec.payment = datadialog->comboPayment->GetValue();

        //Grab the list item selected - Booking Combo Box
        dataRec.booking = datadialog->comboBooking->GetValue();


        if (std::string(dataRec.payment) == "MasterCard")
        {
            bstree->recursiveInsert(dataRec.clientID, dataRec.firstName, dataRec.lastName, dataRec.destination, dataRec.payment, dataRec.booking);
        }

        if (std::string(dataRec.payment) == "Diner")
        {
            avlTree->recursiveInsert(dataRec.clientID, dataRec.firstName, dataRec.lastName, dataRec.destination, dataRec.payment, dataRec.booking);
        }

        if (std::string(dataRec.payment) == "Visa")
        {
            rbTree->insert(dataRec.clientID, dataRec.firstName, dataRec.lastName, dataRec.destination, dataRec.payment, dataRec.booking);
        }

        if (std::string(dataRec.payment) == "Amex")
        {
            splayTree->recursiveInsert(dataRec.clientID, dataRec.firstName, dataRec.lastName, dataRec.destination, dataRec.payment, dataRec.booking);
        }

        if (std::string(dataRec.booking) == "Internet")
        {
            setA->addElement(dataRec.clientID, dataRec.firstName, dataRec.lastName, dataRec.destination, dataRec.payment, dataRec.booking);
        }

        if (std::string(dataRec.booking) == "Walk-in")
        {
            setB->addElement(dataRec.clientID, dataRec.firstName, dataRec.lastName, dataRec.destination, dataRec.payment, dataRec.booking);
        }

        MainEditBox->AppendText(getDataString(dataRec));
	}
	else 	 //if (datadialog->ShowModal() == wxID_CANCEL)
		datadialog->Close();

	datadialog->Destroy();			//Destroy the dialog box
}

//void AssignmentFrame::onDeleteRecord (wxCommandEvent& event)
void AssignmentFrame::onDeleteRecord (wxCommandEvent& WXUNUSED(event))
{
    struct deleteClient clientRec;

	DataDialogDelete *deleteDialog = new DataDialogDelete( wxT("Pelican Travels - Delete Client Record"),
							wxPoint(200,200), wxSize(500,300) );

	if (deleteDialog->ShowModal() == wxID_OK )
	{
        clientRec.clientIDToBeDeleted = deleteDialog->clientIDToBeDeletedEditBox->GetValue();

        bstree->deleteNode(clientRec.clientIDToBeDeleted);
        avlTree->deleteNode(clientRec.clientIDToBeDeleted);
        rbTree->deleteNode(clientRec.clientIDToBeDeleted);
        splayTree->deleteNode(clientRec.clientIDToBeDeleted);
        setA->deleteElement(clientRec.clientIDToBeDeleted);
        setB->deleteElement(clientRec.clientIDToBeDeleted);
    }
}

//==========================================================================
//================== Definition for the BST Functions ======================
//==========================================================================
void AssignmentFrame::onBSTInorder (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n Binary-Search Tree -> Inorder: \n\n\t"));
    MainEditBox->AppendText(bstree->inorderNode());
}

void AssignmentFrame::onBSTPreorder (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n Binary-Search Tree -> Preorder: \n\n\t"));
    MainEditBox->AppendText(bstree->preorderNode());
}

void AssignmentFrame::onBSTPostorder (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n Binary-Search Tree -> Postorder: \n\n\t"));
    MainEditBox->AppendText(bstree->postorderNode());
}

//==========================================================================
//================== Definition for the AVL Functions ======================
//==========================================================================
void AssignmentFrame::onAVLInorder (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n AVL Tree -> Inorder: \n\n\t"));
    MainEditBox->AppendText(avlTree->inorderNode());
}

void AssignmentFrame::onAVLPreorder (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n AVL Tree -> Preorder: \n\n\t"));
    MainEditBox->AppendText(avlTree->preorderNode());
}

void AssignmentFrame::onAVLPostorder (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n AVL Tree -> Postorder: \n\n\t"));
    MainEditBox->AppendText(avlTree->postorderNode());
}

//==========================================================================
//================== Definition for the RB Functions =======================
//==========================================================================
void AssignmentFrame::onRBInorder (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n Red-Black Tree -> Inorder: \n\n\t"));
    MainEditBox->AppendText(rbTree->inorderNode());
}

void AssignmentFrame::onRBPreorder (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n Red-Black Tree -> Preorder: \n\n\t"));
    MainEditBox->AppendText(rbTree->preorderNode());
}

void AssignmentFrame::onRBPostorder (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n Red-Black Tree -> Postorder: \n\n\t"));
    MainEditBox->AppendText(rbTree->postorderNode());
}

//==========================================================================
//================== Definition for the Splay Functions ====================
//==========================================================================
void AssignmentFrame::onSplayInorder (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n Splay Tree -> Inorder: \n\n\t"));
    MainEditBox->AppendText(splayTree->inorderNode());
}

void AssignmentFrame::onSplayPreorder (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n Splay Tree -> Preorder: \n\n\t"));
    MainEditBox->AppendText(splayTree->preorderNode());
}

void AssignmentFrame::onSplayPostorder (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n Splay Tree -> Postorder: \n\n\t"));
    MainEditBox->AppendText(splayTree->postorderNode());
}

//==========================================================================
//================== Definition for the Min Heap Functions =================
//==========================================================================
void AssignmentFrame::onDisplayAllMinHeap (wxCommandEvent& event)
{

}

void AssignmentFrame::onHeapSortMinHeap (wxCommandEvent& event)
{

}

//==========================================================================
//================== Definition for the Max Heap Functions =================
//==========================================================================
void AssignmentFrame::onDisplayAllMaxHeap (wxCommandEvent& event)
{

}

void AssignmentFrame::onHeapSortMaxHeap (wxCommandEvent& event)
{

}

//==========================================================================
//================== Definition for the Set Functions ======================
//==========================================================================
void AssignmentFrame::onDisplaySetA (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n Elements in Set A: \n\n\t"));
    MainEditBox->AppendText(setA->displaySet());
}

void AssignmentFrame::onDisplaySetB (wxCommandEvent& event)
{
    MainEditBox->Clear();
    MainEditBox->AppendText(wxT("\n\n Elements in Set B: \n\n\t"));
    MainEditBox->AppendText(setB->displaySet());
}

void AssignmentFrame::onDisplayIntersection (wxCommandEvent& event)
{
    MainEditBox->Clear();
    intersectionSet->intersectionSet(setA, setB);
    MainEditBox->AppendText(wxT("\n\n Elements in Intersection Set of Set A & Set B: \n\n\t"));
    MainEditBox->AppendText(intersectionSet->displaySet());
}

void AssignmentFrame::onDisplayUnion (wxCommandEvent& event)
{
    MainEditBox->Clear();
    unionSet->unionSet(setA, setB);
    MainEditBox->AppendText(wxT("\n\n Elements in Union Set of Set A & Set B: \n\n\t"));
    MainEditBox->AppendText(unionSet->displaySet());
}

//==========================================================================
//================== Definition for the Help Functions =====================
//==========================================================================

    void AssignmentFrame::onAboutHelp (wxCommandEvent& event){
        wxMessageBox(wxT("Assignment Project 2 \n Version 1.0 \n Caleb Ellis \n The Program is Running on a Linux Virtual Machine"), wxT("About"), wxOK | wxICON_INFORMATION, this);
    };
    void AssignmentFrame::onExitHelp (wxCommandEvent& event){
        wxMessageBox(wxT("Good-bye!"), wxT("Exit"), wxOK | wxICON_INFORMATION, this);
        Close(TRUE); // Close the window
    };
