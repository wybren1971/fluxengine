///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-234-gd93c9fc0-dirty)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "layout.h"

#include "icon.png.h"

///////////////////////////////////////////////////////////////////////////

MainWindowGen::MainWindowGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	menuBar = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( m_menu1, wxID_ABOUT, wxString( wxT("&About") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem2 );

	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( m_menu1, wxID_EXIT, wxString( wxT("E&xit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem1 );

	menuBar->Append( m_menu1, wxT("&File") );

	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Show &logs...") ) + wxT('\t') + wxT("CTRL+L"), wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem3 );

	wxMenuItem* m_menuItem4;
	m_menuItem4 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Show current &configuration...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem4 );

	menuBar->Append( m_menu2, wxT("&View") );

	this->SetMenuBar( menuBar );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	dataNotebook = new wxSimplebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	idlePanel = new wxScrolledWindow( dataNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTAB_TRAVERSAL|wxVSCROLL );
	idlePanel->SetScrollRate( 5, 5 );
	wxGridSizer* gSizer11;
	gSizer11 = new wxGridSizer( 1, 1, 0, 0 );

	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer8->AddGrowableCol( 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	fgSizer8->SetMinSize( wxSize( 400,-1 ) );
	applicationBitmap = new wxStaticBitmap( idlePanel, wxID_ANY, icon_png_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer8->Add( applicationBitmap, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_staticText61 = new wxStaticText( idlePanel, wxID_ANY, wxT("Pick one of:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	fgSizer8->Add( m_staticText61, 0, wxALIGN_CENTER|wxALL, 5 );

	realDiskRadioButton = new wxRadioButton( idlePanel, wxID_ANY, wxT("Real disk"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	realDiskRadioButton->SetToolTip( wxT("You want to use a real floppy drive attached to real hardware.") );

	fgSizer8->Add( realDiskRadioButton, 0, wxALL|wxEXPAND, 5 );

	realDiskRadioButtonPanel = new wxPanel( idlePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	deviceCombo = new wxComboBox( realDiskRadioButtonPanel, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	deviceCombo->SetToolTip( wxT("Device ID to use (either the path of a serial port or a USB serial number).") );

	bSizer3->Add( deviceCombo, 0, wxALL|wxEXPAND, 5 );

	wxString driveChoiceChoices[] = { wxT("drive:0"), wxT("drive:1") };
	int driveChoiceNChoices = sizeof( driveChoiceChoices ) / sizeof( wxString );
	driveChoice = new wxChoice( realDiskRadioButtonPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, driveChoiceNChoices, driveChoiceChoices, 0 );
	driveChoice->SetSelection( 0 );
	driveChoice->SetToolTip( wxT("Which drive on the device to use.") );

	bSizer3->Add( driveChoice, 0, wxALL|wxEXPAND, 5 );

	highDensityToggle = new wxCheckBox( realDiskRadioButtonPanel, wxID_ANY, wxT("This is a high density disk"), wxDefaultPosition, wxDefaultSize, 0 );
	highDensityToggle->SetToolTip( wxT("If you are using a high density disk, select this.\nThis can be detected automatically for 3.5\"\ndisks but needs to be set manually for everything\nelse.") );

	bSizer3->Add( highDensityToggle, 0, wxALL|wxEXPAND, 5 );

	fortyTrackDriveToggle = new wxCheckBox( realDiskRadioButtonPanel, wxID_ANY, wxT("I'm using a 40-track drive"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( fortyTrackDriveToggle, 0, wxALL, 5 );


	realDiskRadioButtonPanel->SetSizer( bSizer3 );
	realDiskRadioButtonPanel->Layout();
	bSizer3->Fit( realDiskRadioButtonPanel );
	fgSizer8->Add( realDiskRadioButtonPanel, 1, wxEXPAND | wxALL, 5 );

	fluxImageRadioButton = new wxRadioButton( idlePanel, wxID_ANY, wxT("Flux image"), wxDefaultPosition, wxDefaultSize, 0 );
	fluxImageRadioButton->SetToolTip( wxT("You want to use an unencoded flux file.") );

	fgSizer8->Add( fluxImageRadioButton, 0, wxALL|wxEXPAND, 5 );

	fluxImageRadioButtonPanel = new wxPanel( idlePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer121;
	gSizer121 = new wxGridSizer( 1, 1, 0, 0 );

	fluxImagePicker = new wxFilePickerCtrl( fluxImageRadioButtonPanel, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL );
	fluxImagePicker->SetToolTip( wxT("Path to a .flux, .scp or other flux file.") );

	gSizer121->Add( fluxImagePicker, 0, wxALL|wxEXPAND, 5 );


	fluxImageRadioButtonPanel->SetSizer( gSizer121 );
	fluxImageRadioButtonPanel->Layout();
	gSizer121->Fit( fluxImageRadioButtonPanel );
	fgSizer8->Add( fluxImageRadioButtonPanel, 1, wxEXPAND | wxALL, 5 );

	diskImageRadioButton = new wxRadioButton( idlePanel, wxID_ANY, wxT("Disk image"), wxDefaultPosition, wxDefaultSize, 0 );
	diskImageRadioButton->SetToolTip( wxT("You want to use a decode file system disk image.") );

	fgSizer8->Add( diskImageRadioButton, 0, wxALL|wxEXPAND, 5 );

	diskImageRadioButtonPanel = new wxPanel( idlePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer1211;
	gSizer1211 = new wxGridSizer( 1, 1, 0, 0 );

	diskImagePicker = new wxFilePickerCtrl( diskImageRadioButtonPanel, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL );
	diskImagePicker->SetToolTip( wxT("The path to the disk image.") );

	gSizer1211->Add( diskImagePicker, 0, wxALL|wxEXPAND, 5 );


	diskImageRadioButtonPanel->SetSizer( gSizer1211 );
	diskImageRadioButtonPanel->Layout();
	gSizer1211->Fit( diskImageRadioButtonPanel );
	fgSizer8->Add( diskImageRadioButtonPanel, 1, wxEXPAND | wxALL, 5 );

	m_staticText23 = new wxStaticText( idlePanel, wxID_ANY, wxT("then select a format:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer8->Add( m_staticText23, 0, wxALIGN_CENTER|wxALL, 5 );

	m_panel11 = new wxPanel( idlePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizer6->AddGrowableCol( 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxArrayString formatChoiceChoices;
	formatChoice = new wxChoice( m_panel11, wxID_ANY, wxDefaultPosition, wxDefaultSize, formatChoiceChoices, 0 );
	formatChoice->SetSelection( 0 );
	formatChoice->SetToolTip( wxT("The format of the disk.") );

	fgSizer6->Add( formatChoice, 0, wxALL|wxEXPAND, 5 );

	customConfigurationButton = new wxButton( m_panel11, wxID_ANY, wxT("Customise..."), wxDefaultPosition, wxDefaultSize, 0 );
	customConfigurationButton->SetToolTip( wxT("Allows you to enter arbitrary configuration parameters.") );

	fgSizer6->Add( customConfigurationButton, 0, wxALL, 5 );


	m_panel11->SetSizer( fgSizer6 );
	m_panel11->Layout();
	fgSizer6->Fit( m_panel11 );
	fgSizer8->Add( m_panel11, 1, wxEXPAND | wxALL, 5 );

	m_staticText19 = new wxStaticText( idlePanel, wxID_ANY, wxT("and press one of:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	fgSizer8->Add( m_staticText19, 0, wxALIGN_CENTER|wxALL, 5 );

	wxGridSizer* gSizer9;
	gSizer9 = new wxGridSizer( 1, 0, 0, 0 );

	readButton = new wxButton( idlePanel, wxID_ANY, wxT("Read disk"), wxDefaultPosition, wxDefaultSize, 0 );
	readButton->SetLabelMarkup( wxT("Read disk") );
	readButton->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR ) );
	readButton->SetToolTip( wxT("Read and decode, producing a disk image from a real disk or flux file.") );

	gSizer9->Add( readButton, 0, wxALL|wxEXPAND, 5 );

	writeButton = new wxButton( idlePanel, wxID_ANY, wxT("Write disk"), wxDefaultPosition, wxDefaultSize, 0 );

	writeButton->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_TOOLBAR ) );
	writeButton->SetBitmapDisabled( wxNullBitmap );
	writeButton->SetToolTip( wxT("Encode and write to either a real disk or a flux file.") );

	gSizer9->Add( writeButton, 0, wxALL|wxEXPAND, 5 );

	browseButton = new wxButton( idlePanel, wxID_ANY, wxT("Browse disk"), wxDefaultPosition, wxDefaultSize, 0 );

	browseButton->SetBitmap( wxArtProvider::GetBitmap( wxART_FOLDER_OPEN, wxART_TOOLBAR ) );
	browseButton->SetToolTip( wxT("Access the files on the disk directly without needing to image it.") );

	gSizer9->Add( browseButton, 0, wxALL|wxEXPAND, 5 );

	formatButton = new wxButton( idlePanel, wxID_ANY, wxT("Format disk"), wxDefaultPosition, wxDefaultSize, 0 );

	formatButton->SetBitmap( wxArtProvider::GetBitmap( wxART_DELETE, wxART_BUTTON ) );
	gSizer9->Add( formatButton, 0, wxALL|wxEXPAND, 5 );


	fgSizer8->Add( gSizer9, 1, wxEXPAND, 5 );


	gSizer11->Add( fgSizer8, 1, wxALIGN_CENTER|wxALL, 5 );


	idlePanel->SetSizer( gSizer11 );
	idlePanel->Layout();
	gSizer11->Fit( idlePanel );
	dataNotebook->AddPage( idlePanel, wxT("a page"), false );
	imagePanel = new wxPanel( dataNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxVERTICAL );

	imagerToolbar = new wxAuiToolBar( imagePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT|wxAUI_TB_TEXT );
	imagerBackTool = imagerToolbar->AddTool( wxID_ANY, wxT("Back"), wxArtProvider::GetBitmap( wxART_GO_BACK, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	imagerToolbar->Realize();

	bSizer41->Add( imagerToolbar, 0, wxEXPAND, 5 );

	wxGridSizer* gSizer122;
	gSizer122 = new wxGridSizer( 0, 2, 0, 0 );

	wxGridSizer* gSizer5;
	gSizer5 = new wxGridSizer( 0, 1, 0, 0 );

	visualiser = new VisualisationControl( imagePanel, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxBORDER_THEME );
	gSizer5->Add( visualiser, 0, wxALL|wxEXPAND, 5 );


	gSizer122->Add( gSizer5, 1, wxEXPAND, 5 );

	wxGridSizer* gSizer7;
	gSizer7 = new wxGridSizer( 1, 1, 0, 0 );

	wxGridSizer* gSizer8;
	gSizer8 = new wxGridSizer( 0, 1, 0, 0 );

	imagerSaveImageButton = new wxButton( imagePanel, wxID_ANY, wxT("Save decoded image"), wxDefaultPosition, wxDefaultSize, 0 );

	imagerSaveImageButton->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_BUTTON ) );
	gSizer8->Add( imagerSaveImageButton, 0, wxALL|wxEXPAND, 5 );

	imagerSaveFluxButton = new wxButton( imagePanel, wxID_ANY, wxT("Save raw flux"), wxDefaultPosition, wxDefaultSize, 0 );

	imagerSaveFluxButton->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_SAVE_AS, wxART_BUTTON ) );
	gSizer8->Add( imagerSaveFluxButton, 0, wxALL|wxEXPAND, 5 );

	m_staticText4 = new wxStaticText( imagePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer8->Add( m_staticText4, 0, wxALL, 5 );

	imagerGoAgainButton = new wxButton( imagePanel, wxID_ANY, wxT("Go again"), wxDefaultPosition, wxDefaultSize, 0 );

	imagerGoAgainButton->SetBitmap( wxArtProvider::GetBitmap( wxART_REDO, wxART_BUTTON ) );
	gSizer8->Add( imagerGoAgainButton, 0, wxALL|wxEXPAND, 5 );


	gSizer7->Add( gSizer8, 1, wxALIGN_CENTER, 5 );


	gSizer122->Add( gSizer7, 1, wxEXPAND, 5 );


	bSizer41->Add( gSizer122, 1, wxEXPAND, 5 );


	imagePanel->SetSizer( bSizer41 );
	imagePanel->Layout();
	bSizer41->Fit( imagePanel );
	dataNotebook->AddPage( imagePanel, wxT("a page"), false );
	browsePanel = new wxPanel( dataNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer23;
	fgSizer23 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer23->AddGrowableCol( 0 );
	fgSizer23->AddGrowableRow( 1 );
	fgSizer23->SetFlexibleDirection( wxBOTH );
	fgSizer23->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	browserToolbar = new wxAuiToolBar( browsePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT|wxAUI_TB_TEXT );
	browserBackTool = browserToolbar->AddTool( wxID_ANY, wxT("Back"), wxArtProvider::GetBitmap( wxART_GO_BACK, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	browserToolbar->AddSeparator();

	browserInfoTool = browserToolbar->AddTool( wxID_ANY, wxT("Info"), wxArtProvider::GetBitmap( wxART_INFORMATION, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	browserViewTool = browserToolbar->AddTool( wxID_ANY, wxT("View"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	browserSaveTool = browserToolbar->AddTool( wxID_ANY, wxT("Save"), wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	browserMoreMenuButton = browserToolbar->AddTool( wxID_ANY, wxT("More"), wxArtProvider::GetBitmap( wxART_PLUS, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );
	browserToolbar->SetToolDropDown( browserMoreMenuButton->GetId(), true );

	browserMoreMenu = new wxMenu();
	browserAddMenuItem = new wxMenuItem( browserMoreMenu, wxID_ANY, wxString( wxT("Add file") ) , wxEmptyString, wxITEM_NORMAL );
	browserMoreMenu->Append( browserAddMenuItem );

	browserNewDirectoryMenuItem = new wxMenuItem( browserMoreMenu, wxID_ANY, wxString( wxT("New directory") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	browserNewDirectoryMenuItem->SetBitmaps( wxNullBitmap );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	browserNewDirectoryMenuItem->SetBitmap( wxNullBitmap );
	#endif
	browserMoreMenu->Append( browserNewDirectoryMenuItem );

	browserRenameMenuItem = new wxMenuItem( browserMoreMenu, wxID_ANY, wxString( wxT("Move file") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	browserRenameMenuItem->SetBitmaps( wxNullBitmap );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	browserRenameMenuItem->SetBitmap( wxNullBitmap );
	#endif
	browserMoreMenu->Append( browserRenameMenuItem );

	browserDeleteMenuItem = new wxMenuItem( browserMoreMenu, wxID_ANY, wxString( wxT("Delete file") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	browserDeleteMenuItem->SetBitmaps( wxNullBitmap );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	browserDeleteMenuItem->SetBitmap( wxNullBitmap );
	#endif
	browserMoreMenu->Append( browserDeleteMenuItem );

	browserToolbar->Connect( browserMoreMenuButton->GetId(), wxEVT_COMMAND_AUITOOLBAR_TOOL_DROPDOWN, wxAuiToolBarEventHandler( MainWindowGen::browserMoreMenuButtonOnDropDownMenu ), NULL, this );


	browserToolbar->AddSeparator();

	browserFormatTool = browserToolbar->AddTool( wxID_ANY, wxT("Format"), wxArtProvider::GetBitmap( wxART_DELETE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	browserToolbar->Realize();

	fgSizer23->Add( browserToolbar, 0, wxEXPAND, 5 );

	browserTree = new wxDataViewCtrl( browsePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_SINGLE );
	m_dataViewColumn1 = browserTree->AppendIconTextColumn( wxT("Filename"), 0, wxDATAVIEW_CELL_EDITABLE, 250, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE );
	m_dataViewColumn2 = browserTree->AppendTextColumn( wxT("Size"), 1, wxDATAVIEW_CELL_INERT, 100, static_cast<wxAlignment>(wxALIGN_RIGHT), wxDATAVIEW_COL_RESIZABLE );
	m_dataViewColumn3 = browserTree->AppendTextColumn( wxT("Mode"), 2, wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE );
	fgSizer23->Add( browserTree, 0, wxALL|wxEXPAND, 5 );

	diskSpaceGauge = new wxGauge( browsePanel, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL|wxGA_SMOOTH );
	diskSpaceGauge->SetValue( 0 );
	fgSizer23->Add( diskSpaceGauge, 0, wxALL|wxEXPAND, 5 );

	wxGridSizer* gSizer12;
	gSizer12 = new wxGridSizer( 0, 2, 0, 0 );

	browserDiscardButton = new wxButton( browsePanel, wxID_ANY, wxT("Discard pending changes"), wxDefaultPosition, wxDefaultSize, 0 );

	browserDiscardButton->SetBitmap( wxArtProvider::GetBitmap( wxART_WARNING, wxART_BUTTON ) );
	gSizer12->Add( browserDiscardButton, 0, wxALIGN_CENTER|wxALL, 5 );

	browserCommitButton = new wxButton( browsePanel, wxID_ANY, wxT("Commit pending changes to disk"), wxDefaultPosition, wxDefaultSize, 0 );

	browserCommitButton->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_BUTTON ) );
	gSizer12->Add( browserCommitButton, 0, wxALIGN_CENTER|wxALL, 5 );


	fgSizer23->Add( gSizer12, 1, wxEXPAND, 5 );

	m_staticText12 = new wxStaticText( browsePanel, wxID_ANY, wxT("No changes will be written until the 'commit' button is pressed."), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText12->Wrap( -1 );
	fgSizer23->Add( m_staticText12, 0, wxALL|wxEXPAND, 5 );


	browsePanel->SetSizer( fgSizer23 );
	browsePanel->Layout();
	fgSizer23->Fit( browsePanel );
	dataNotebook->AddPage( browsePanel, wxT("a page"), false );

	bSizer4->Add( dataNotebook, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainWindowGen::OnClose ) );
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindowGen::OnAboutMenuItem ), this, m_menuItem2->GetId());
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindowGen::OnExit ), this, m_menuItem1->GetId());
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindowGen::OnShowLogWindow ), this, m_menuItem3->GetId());
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindowGen::OnShowConfigWindow ), this, m_menuItem4->GetId());
	realDiskRadioButton->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MainWindowGen::OnConfigRadioButtonClicked ), NULL, this );
	deviceCombo->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainWindowGen::OnControlsChanged ), NULL, this );
	driveChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainWindowGen::OnControlsChanged ), NULL, this );
	highDensityToggle->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainWindowGen::OnControlsChanged ), NULL, this );
	fluxImageRadioButton->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MainWindowGen::OnConfigRadioButtonClicked ), NULL, this );
	fluxImagePicker->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( MainWindowGen::OnControlsChanged ), NULL, this );
	diskImageRadioButton->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MainWindowGen::OnConfigRadioButtonClicked ), NULL, this );
	diskImagePicker->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( MainWindowGen::OnControlsChanged ), NULL, this );
	formatChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainWindowGen::OnControlsChanged ), NULL, this );
	customConfigurationButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnCustomConfigurationButton ), NULL, this );
	readButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnReadButton ), NULL, this );
	writeButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnWriteButton ), NULL, this );
	browseButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowseButton ), NULL, this );
	formatButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnFormatButton ), NULL, this );
	this->Connect( imagerBackTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainWindowGen::OnBackButton ) );
	imagerSaveImageButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnSaveImageButton ), NULL, this );
	imagerSaveFluxButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnSaveFluxButton ), NULL, this );
	imagerGoAgainButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnImagerGoAgainButton ), NULL, this );
	this->Connect( browserBackTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainWindowGen::OnBackButton ) );
	this->Connect( browserInfoTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowserInfoButton ) );
	this->Connect( browserViewTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowserViewButton ) );
	this->Connect( browserSaveTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowserSaveButton ) );
	browserMoreMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindowGen::OnBrowserAddMenuItem ), this, browserAddMenuItem->GetId());
	browserMoreMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindowGen::OnBrowserNewDirectoryMenuItem ), this, browserNewDirectoryMenuItem->GetId());
	browserMoreMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindowGen::OnBrowserRenameMenuItem ), this, browserRenameMenuItem->GetId());
	browserMoreMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindowGen::OnBrowserDeleteMenuItem ), this, browserDeleteMenuItem->GetId());
	this->Connect( browserFormatTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowserFormatButton ) );
	browserTree->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_BEGIN_DRAG, wxDataViewEventHandler( MainWindowGen::OnBrowserBeginDrag ), NULL, this );
	browserTree->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_DROP, wxDataViewEventHandler( MainWindowGen::OnBrowserDrop ), NULL, this );
	browserTree->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_DROP_POSSIBLE, wxDataViewEventHandler( MainWindowGen::OnBrowserDropPossible ), NULL, this );
	browserTree->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_EDITING_DONE, wxDataViewEventHandler( MainWindowGen::OnBrowserFilenameChanged ), NULL, this );
	browserTree->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_EXPANDING, wxDataViewEventHandler( MainWindowGen::OnBrowserDirectoryExpanding ), NULL, this );
	browserTree->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( MainWindowGen::OnBrowserSelectionChanged ), NULL, this );
	browserDiscardButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowserDiscardButton ), NULL, this );
	browserCommitButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowserCommitButton ), NULL, this );
}

MainWindowGen::~MainWindowGen()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainWindowGen::OnClose ) );
	realDiskRadioButton->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MainWindowGen::OnConfigRadioButtonClicked ), NULL, this );
	deviceCombo->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainWindowGen::OnControlsChanged ), NULL, this );
	driveChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainWindowGen::OnControlsChanged ), NULL, this );
	highDensityToggle->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainWindowGen::OnControlsChanged ), NULL, this );
	fluxImageRadioButton->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MainWindowGen::OnConfigRadioButtonClicked ), NULL, this );
	fluxImagePicker->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( MainWindowGen::OnControlsChanged ), NULL, this );
	diskImageRadioButton->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MainWindowGen::OnConfigRadioButtonClicked ), NULL, this );
	diskImagePicker->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( MainWindowGen::OnControlsChanged ), NULL, this );
	formatChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainWindowGen::OnControlsChanged ), NULL, this );
	customConfigurationButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnCustomConfigurationButton ), NULL, this );
	readButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnReadButton ), NULL, this );
	writeButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnWriteButton ), NULL, this );
	browseButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowseButton ), NULL, this );
	formatButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnFormatButton ), NULL, this );
	this->Disconnect( imagerBackTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainWindowGen::OnBackButton ) );
	imagerSaveImageButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnSaveImageButton ), NULL, this );
	imagerSaveFluxButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnSaveFluxButton ), NULL, this );
	imagerGoAgainButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnImagerGoAgainButton ), NULL, this );
	this->Disconnect( browserBackTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainWindowGen::OnBackButton ) );
	this->Disconnect( browserInfoTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowserInfoButton ) );
	this->Disconnect( browserViewTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowserViewButton ) );
	this->Disconnect( browserSaveTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowserSaveButton ) );
	this->Disconnect( browserFormatTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowserFormatButton ) );
	browserTree->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_BEGIN_DRAG, wxDataViewEventHandler( MainWindowGen::OnBrowserBeginDrag ), NULL, this );
	browserTree->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_DROP, wxDataViewEventHandler( MainWindowGen::OnBrowserDrop ), NULL, this );
	browserTree->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_DROP_POSSIBLE, wxDataViewEventHandler( MainWindowGen::OnBrowserDropPossible ), NULL, this );
	browserTree->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_EDITING_DONE, wxDataViewEventHandler( MainWindowGen::OnBrowserFilenameChanged ), NULL, this );
	browserTree->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_EXPANDING, wxDataViewEventHandler( MainWindowGen::OnBrowserDirectoryExpanding ), NULL, this );
	browserTree->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( MainWindowGen::OnBrowserSelectionChanged ), NULL, this );
	browserDiscardButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowserDiscardButton ), NULL, this );
	browserCommitButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindowGen::OnBrowserCommitButton ), NULL, this );

	delete browserMoreMenu;
}

TextViewerWindowGen::TextViewerWindowGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer8->AddGrowableCol( 0 );
	fgSizer8->AddGrowableRow( 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	textControl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH );
	textControl->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	fgSizer8->Add( textControl, 0, wxALL|wxEXPAND, 5 );

	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2->Realize();

	fgSizer8->Add( m_sdbSizer2, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( fgSizer8 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TextViewerWindowGen::OnClose ) );
	m_sdbSizer2OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TextViewerWindowGen::OnClose ), NULL, this );
}

TextViewerWindowGen::~TextViewerWindowGen()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TextViewerWindowGen::OnClose ) );
	m_sdbSizer2OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TextViewerWindowGen::OnClose ), NULL, this );

}

FluxViewerWindowGen::FluxViewerWindowGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 200,100 ), wxDefaultSize );

	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer5->AddGrowableCol( 0 );
	fgSizer5->AddGrowableRow( 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	fluxviewer = new FluxViewerControl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( fluxviewer, 1, wxEXPAND, 5 );

	scrollbar = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	fgSizer5->Add( scrollbar, 0, wxALIGN_BOTTOM|wxEXPAND, 5 );

	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2->Realize();

	fgSizer5->Add( m_sdbSizer2, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( fgSizer5 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FluxViewerWindowGen::OnClose ) );
	m_sdbSizer2OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FluxViewerWindowGen::OnClose ), NULL, this );
}

FluxViewerWindowGen::~FluxViewerWindowGen()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FluxViewerWindowGen::OnClose ) );
	m_sdbSizer2OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FluxViewerWindowGen::OnClose ), NULL, this );

}

TextEditorWindowGen::TextEditorWindowGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer8->AddGrowableCol( 0 );
	fgSizer8->AddGrowableRow( 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	textControl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_PROCESS_TAB );
	textControl->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	fgSizer8->Add( textControl, 0, wxALL|wxEXPAND, 5 );

	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2Save = new wxButton( this, wxID_SAVE );
	m_sdbSizer2->AddButton( m_sdbSizer2Save );
	m_sdbSizer2Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer2->AddButton( m_sdbSizer2Cancel );
	m_sdbSizer2->Realize();

	fgSizer8->Add( m_sdbSizer2, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( fgSizer8 );
	this->Layout();
	fgSizer8->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TextEditorWindowGen::OnClose ) );
	m_sdbSizer2Cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TextEditorWindowGen::OnCancel ), NULL, this );
	m_sdbSizer2Save->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TextEditorWindowGen::OnSave ), NULL, this );
}

TextEditorWindowGen::~TextEditorWindowGen()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TextEditorWindowGen::OnClose ) );
	m_sdbSizer2Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TextEditorWindowGen::OnCancel ), NULL, this );
	m_sdbSizer2Save->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TextEditorWindowGen::OnSave ), NULL, this );

}

FileViewerWindowGen::FileViewerWindowGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer8->AddGrowableCol( 0 );
	fgSizer8->AddGrowableRow( 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel8 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer101;
	gSizer101 = new wxGridSizer( 1, 1, 0, 0 );

	textControl = new wxTextCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	textControl->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	gSizer101->Add( textControl, 0, wxALL|wxEXPAND, 5 );


	m_panel8->SetSizer( gSizer101 );
	m_panel8->Layout();
	gSizer101->Fit( m_panel8 );
	m_notebook1->AddPage( m_panel8, wxT("Text"), false );
	m_panel7 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer10;
	gSizer10 = new wxGridSizer( 1, 1, 0, 0 );

	hexControl = new wxTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	hexControl->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	gSizer10->Add( hexControl, 0, wxALL|wxEXPAND, 5 );


	m_panel7->SetSizer( gSizer10 );
	m_panel7->Layout();
	gSizer10->Fit( m_panel7 );
	m_notebook1->AddPage( m_panel7, wxT("Hex"), false );

	fgSizer8->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );

	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2->Realize();

	fgSizer8->Add( m_sdbSizer2, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( fgSizer8 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_sdbSizer2OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FileViewerWindowGen::OnClose ), NULL, this );
}

FileViewerWindowGen::~FileViewerWindowGen()
{
	// Disconnect Events
	m_sdbSizer2OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FileViewerWindowGen::OnClose ), NULL, this );

}

GetfileDialog::GetfileDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("File on disk:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	gbSizer1->Add( m_staticText7, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	filenameText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), wxTE_READONLY );
	filenameText->Enable( false );

	gbSizer1->Add( filenameText, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("File to save as:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	gbSizer1->Add( m_staticText9, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	targetFilePicker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_OVERWRITE_PROMPT|wxFLP_SAVE|wxFLP_USE_TEXTCTRL );
	gbSizer1->Add( targetFilePicker, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	buttons_ = new wxStdDialogButtonSizer();
	buttons_OK = new wxButton( this, wxID_OK );
	buttons_->AddButton( buttons_OK );
	buttons_Cancel = new wxButton( this, wxID_CANCEL );
	buttons_->AddButton( buttons_Cancel );
	buttons_->Realize();

	gbSizer1->Add( buttons_, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );


	this->SetSizer( gbSizer1 );
	this->Layout();
	gbSizer1->Fit( this );

	this->Centre( wxBOTH );
}

GetfileDialog::~GetfileDialog()
{
}

FileConflictDialog::FileConflictDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText91 = new wxStaticText( this, wxID_ANY, wxT("That name is already in use.\nPlease specify another:"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText91->Wrap( -1 );
	gbSizer1->Add( m_staticText91, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Old name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	gbSizer1->Add( m_staticText7, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	newNameText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	gbSizer1->Add( newNameText, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("New name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	gbSizer1->Add( m_staticText9, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	oldNameText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	oldNameText->Enable( false );

	gbSizer1->Add( oldNameText, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	buttons_ = new wxStdDialogButtonSizer();
	buttons_OK = new wxButton( this, wxID_OK );
	buttons_->AddButton( buttons_OK );
	buttons_Cancel = new wxButton( this, wxID_CANCEL );
	buttons_->AddButton( buttons_Cancel );
	buttons_->Realize();

	gbSizer1->Add( buttons_, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );


	this->SetSizer( gbSizer1 );
	this->Layout();
	gbSizer1->Fit( this );

	this->Centre( wxBOTH );
}

FileConflictDialog::~FileConflictDialog()
{
}

FileRenameDialog::FileRenameDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText91 = new wxStaticText( this, wxID_ANY, wxT("Please specify the new name\n(and path) of the file."), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText91->Wrap( -1 );
	gbSizer1->Add( m_staticText91, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Old name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	gbSizer1->Add( m_staticText7, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	newNameText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	gbSizer1->Add( newNameText, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("New name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	gbSizer1->Add( m_staticText9, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	oldNameText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	oldNameText->Enable( false );

	gbSizer1->Add( oldNameText, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	buttons_ = new wxStdDialogButtonSizer();
	buttons_OK = new wxButton( this, wxID_OK );
	buttons_->AddButton( buttons_OK );
	buttons_Cancel = new wxButton( this, wxID_CANCEL );
	buttons_->AddButton( buttons_Cancel );
	buttons_->Realize();

	gbSizer1->Add( buttons_, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );


	this->SetSizer( gbSizer1 );
	this->Layout();
	gbSizer1->Fit( this );

	this->Centre( wxBOTH );
}

FileRenameDialog::~FileRenameDialog()
{
}

CreateDirectoryDialog::CreateDirectoryDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText91 = new wxStaticText( this, wxID_ANY, wxT("Please specify the name (and path)\nof the new directory."), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText91->Wrap( -1 );
	gbSizer1->Add( m_staticText91, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	newNameText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	gbSizer1->Add( newNameText, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	gbSizer1->Add( m_staticText9, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	buttons_ = new wxStdDialogButtonSizer();
	buttons_OK = new wxButton( this, wxID_OK );
	buttons_->AddButton( buttons_OK );
	buttons_Cancel = new wxButton( this, wxID_CANCEL );
	buttons_->AddButton( buttons_Cancel );
	buttons_->Realize();

	gbSizer1->Add( buttons_, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );


	this->SetSizer( gbSizer1 );
	this->Layout();
	gbSizer1->Fit( this );

	this->Centre( wxBOTH );
}

CreateDirectoryDialog::~CreateDirectoryDialog()
{
}

FormatDialog::FormatDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText91 = new wxStaticText( this, wxID_ANY, wxT("This will erase the entire disk. (But remember that\nyou can always undo changes until you press the 'commit changes' button.)"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText91->Wrap( -1 );
	gbSizer1->Add( m_staticText91, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Volume name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	gbSizer1->Add( m_staticText7, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	volumeNameText = new wxTextCtrl( this, wxID_ANY, wxT("FluxEngineDisk"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( volumeNameText, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	quickFormatCheckBox = new wxCheckBox( this, wxID_ANY, wxT("Quick format: if the disk is not already correctly formatted,\nvery bad things will happen!"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( quickFormatCheckBox, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	buttons_ = new wxStdDialogButtonSizer();
	buttons_OK = new wxButton( this, wxID_OK );
	buttons_->AddButton( buttons_OK );
	buttons_Cancel = new wxButton( this, wxID_CANCEL );
	buttons_->AddButton( buttons_Cancel );
	buttons_->Realize();

	gbSizer1->Add( buttons_, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );


	this->SetSizer( gbSizer1 );
	this->Layout();
	gbSizer1->Fit( this );

	this->Centre( wxBOTH );
}

FormatDialog::~FormatDialog()
{
}
