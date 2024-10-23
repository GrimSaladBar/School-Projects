//
//  DataDialog.h
//  DataDialog
//
//  Created by Dr. John Charlery on 10/19/2023.
//  Copyright (c) 2023 Dr. John Charlery. All rights reserved.
//

#ifndef DATADIALOG_H
#define DATADIALOG_H


struct data
{
	long		clientID;
	wxString	firstName;
	wxString	lastName;
	wxString	destination;
	wxString	payment;
	wxString	booking;
};

struct deleteClient
{
	long clientIDToBeDeleted;
};

//Define a dialog box class with 10 data fields (Attributes) - inheriting from wxDialog, of course 
class DataDialog : public wxDialog
  {
	 public:
		DataDialog(const wxString& title, const wxPoint& pos, const wxSize& size);


		wxSpinCtrl* clientIDEditBox;						// Integer spin control


		wxTextCtrl* firstNameEditBox;						// Text control boxes
		wxTextCtrl* lastNameEditBox;
		wxTextCtrl* destinationEditBox;
		
		wxComboBox* comboPayment;								//For a drop-down list
		wxComboBox* comboBooking;
  };

class DataDialogDelete : public wxDialog
{
	public:
		DataDialogDelete(const wxString& title, const wxPoint& pos, const wxSize& size);

		wxSpinCtrl* clientIDToBeDeletedEditBox;
};
  
DataDialog::DataDialog ( const wxString& title, const wxPoint& pos, 
		   const wxSize& size): wxDialog((wxDialog *)NULL, -1, title, pos, size)
  {
		//Set up the panel
  		wxPanel    *panel = new wxPanel(this, -1);
 
		//Define and position the StaticTexts - ie the labels
		wxStaticText* clientIDLabel = new wxStaticText(panel, wxID_ANY, wxT("ID Number:"), wxPoint(15, 28) );
		wxStaticText* firstNameLabel = new wxStaticText(panel, wxID_ANY, wxT("First Name:"), wxPoint(15, 68) );
		wxStaticText* lastNameLabel = new wxStaticText(panel, wxID_ANY, wxT("Surname:"), wxPoint(15, 108));
		wxStaticText* destinationLabel  = new wxStaticText(panel, wxID_ANY, wxT("Destination:"), wxPoint(15, 148) );
		wxStaticText* paymentLabel = new wxStaticText(panel, wxID_ANY, wxT("Payment:"), wxPoint(317, 40) );
		wxStaticText* bookingLabel = new wxStaticText(panel, wxID_ANY, wxT("Booking:"), wxPoint(317, 108) );


		//Define and position the Integer data Box
		clientIDEditBox = new wxSpinCtrl(panel, -1, wxT("99999"), wxPoint(100, 25), wxSize(150, -1),
									 wxSP_ARROW_KEYS, 11111, 999999, 100);
		firstNameEditBox 	=  new wxTextCtrl ( panel, wxID_ANY, wxT("-- First Name--"),
						    wxPoint(100, 65), wxSize(170, -1) );
		lastNameEditBox 	=  new wxTextCtrl ( panel, wxID_ANY, wxT("--Surname--"),
						    wxPoint(100, 105), wxSize(170, -1) );
		destinationEditBox 	=  new wxTextCtrl ( panel, wxID_ANY, wxT("--Destination--"),
						    wxPoint(100, 145), wxSize(170, -1) );
		
		//Define and position a drop-down list
		wxArrayString paymentArray;
		paymentArray.Add(wxT("Amex"));
		paymentArray.Add(wxT("Diner"));
		paymentArray.Add(wxT("MasterCard"));
		paymentArray.Add(wxT("Visa"));

        comboPayment = new wxComboBox(panel, -1, wxT("Amex"), wxPoint(315, 65),
				       wxSize(120, -1), paymentArray, wxCB_READONLY);
				       //wxCB_DROPDOWN

		wxArrayString bookingArray;
		bookingArray.Add(wxT("Gifted"));
		bookingArray.Add(wxT("Internet"));
		bookingArray.Add(wxT("Telephone"));
		bookingArray.Add(wxT("Walk-in"));

        comboBooking = new wxComboBox(panel, -1, wxT("Gifted"), wxPoint(315, 135),
				       wxSize(120, -1), bookingArray, wxCB_READONLY);
				       //wxCB_DROPDOWN

		// Define and position the Response buttons (OK and CANCEL)
		
		// The OK button
		wxButton* ok = new wxButton(panel, wxID_OK, wxT("&OK"), 
					    wxPoint(150, 205), wxDefaultSize, 0);

		// The CANCEL button
		wxButton* cancel = new wxButton ( panel, wxID_CANCEL, wxT("&CANCEL"), 
						  wxPoint(270, 205), wxDefaultSize, 0 );
		
  		// Centre the dialog on the parent's window
		Centre();

  //      Maximize(); // Maximize the window
		
  }

DataDialogDelete::DataDialogDelete ( const wxString& title, const wxPoint& pos,
		   const wxSize& size): wxDialog((wxDialog *)NULL, -1, title, pos, size)
  {
		//Set up the panel
  		wxPanel    *panel = new wxPanel(this, -1);

		//Define and position the StaticTexts - ie the labels
		wxStaticText* clientIDToBeDeletedLabel = new wxStaticText(panel, wxID_ANY, wxT("ID Number:"), wxPoint(160, 120) );

		//Define and position the Integer data Box
		clientIDToBeDeletedEditBox = new wxSpinCtrl(panel, -1, wxT("99999"), wxPoint(160, 160), wxSize(150, -1),
									 wxSP_ARROW_KEYS, 11111, 999999, 100);

		// Define and position the Response buttons (OK and CANCEL)

		// The OK button
		wxButton* ok = new wxButton(panel, wxID_OK, wxT("&OK"),
					    wxPoint(150, 205), wxDefaultSize, 0);

		// The CANCEL button
		wxButton* cancel = new wxButton ( panel, wxID_CANCEL, wxT("&CANCEL"),
						  wxPoint(270, 205), wxDefaultSize, 0 );

  		// Centre the dialog on the parent's window
		Centre();

  //      Maximize(); // Maximize the window

  }

wxString getDataString(struct data dataRec)
{
	wxString str;

	wxString intNum;
	intNum << dataRec.clientID;

	str.Append(intNum);
	str.Append(wxT("\t"));
	str.Append(dataRec.firstName);
	str.Append(wxT("\t"));
	str.Append(dataRec.lastName);
	str.Append(wxT("\t"));
	str.Append(dataRec.destination);
	str.Append(wxT("\t"));
	str.Append(dataRec.payment);
	str.Append(wxT("\t"));
	str.Append(dataRec.booking);
	str.Append(wxT("\n"));
	
	return str;
}
#endif
