#include "../include/sysinc.h"
#include "../include/qtinc.h"
#include "../include/item.h"

Item::Item(ItemList* pl, MainWindow* mw, bool created_from_settings, ItemType _type)
{
	parent_list = pl;
	parent_window = mw;
	type = _type;

	next_item = 0;
	prev_item = parent_list->LastItem();

	if (!parent_list->FirstItem())
	{
		parent_list->SetFirstItem(this);
		index = 0;
	}
	else
	{
		parent_list->LastItem()->next_item = this;
		index = prev_item->index + 1;
	}
	parent_list->SetLastItem(this);
	SetupUi();
}

Item::~Item()
{
	if (next_item)
		next_item->prev_item = prev_item;
	else
		parent_list->SetLastItem(prev_item);

	if (prev_item)
		prev_item->next_item = next_item;
	else
		parent_list->SetFirstItem(next_item);
	NumberElements();
	if (parent_list->LastItem() && parent_list->LastItem()->index <= max_number_chars - 1)
	{
		QPushButton* b;
		switch (type)
		{
			case map: b = parent_window->add_map_button; break;
			case character: b = parent_window->add_char_button; break;
		}
		b->setEnabled(true);
	}
}

void Item::SetupUi()
{
   QBoxLayout* item_layout;
	if (type == character)
		item_layout = parent_window->char_vert_layout;
	else if (type == map)
		item_layout = parent_window->map_vert_layout;

	group_box = new QGroupBox();
	group_box->setFixedSize(618, 150);

	label = new QLabel(group_box);
	label->setText(QString(type == character ? "Character #%1" : "Map #%1").arg(index + 1));
	name_label = new QLabel(group_box);
	name_label->setText("Name:");
	name_label->move(10, 110);

	delete_button = new QToolButton(group_box);
	delete_button->setAutoFillBackground(true);
	delete_button->setGeometry(600, 19, 15, 15);
	delete_button->setIcon(QIcon("rc/img/delete.png"));
	delete_button->setIconSize(QSize(40, 40));

	img_edit = new QLineEdit(group_box);
	img_edit->setGeometry(QRect(100, 40, 400, 21));
	img_edit->setReadOnly(true);

	img_button = new QPushButton("Browse", group_box);
	img_button->move(10, 40);

	img_label = new QLabel(group_box);
	img_label->setText("Preview image:");
	img_label->move(10, 25);

	model_edit = new QLineEdit(group_box);
	model_edit->setGeometry(QRect(100, 80, 400, 21)); 
	model_edit->setReadOnly(true);

	model_button = new QPushButton("Browse", group_box);
	model_button->move(10, 80);

	model_label = new QLabel(group_box);
	model_label->setText("Model for character:");
	model_label->move(10, 65);

	name_edit = new QLineEdit(group_box);
	name_edit->setGeometry(QRect(100, 105, 180, 21));

	g_view = new QGraphicsView(group_box);
	g_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	g_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	g_view->setGeometry(QRect(510, 40, 100, 100));
	g_scene = new QGraphicsScene(QRectF(0, 0, g_view->geometry().width(), g_view->geometry().height()), 0);
	pixmap = new QPixmap;

	item_layout->addWidget(group_box);

	connect(delete_button, SIGNAL(clicked()), this, SLOT(DeleteClicked()));
	connect(img_button, SIGNAL(clicked()), this, SLOT(ImgButtonClicked()));
	connect(model_button, SIGNAL(clicked()), this, SLOT(ModelButtonClicked()));
	connect(img_edit, SIGNAL(textChanged(QString)), this, SLOT(UpdateImage()));

	/*created_from_settings says if this object was created while reading the settings. In ReadSettings(), the texts in the lineedits are changed which would trigger these Signals and set settings_saved to false, so if created from settings, these slots will be connected later*/
	if (!created_from_settings)
	{
		connect(img_edit, SIGNAL(textChanged(QString)), this, SLOT(SettingChanged()));
		connect(model_edit, SIGNAL(textChanged(QString)), this, SLOT(SettingChanged()));
		connect(name_edit, SIGNAL(textChanged(QString)), this, SLOT(SettingChanged()));
	}
}

void Item::Show()
{
	group_box->show();
	label->show();
	name_label->show();
	delete_button->show();
	img_edit->show();    
	model_edit->show();  
	img_button->show();    
	model_button->show();                           
	img_label->show();
	model_label->show();
	name_edit->show();
	g_view->show();
}                       

void Item::DeleteClicked()
{
	group_box->hide();
	label->hide();
	delete_button->hide();
	delete this;
}

void Item::NumberElements()
{
	int i = 0;
	Item* c;
	c = parent_list->FirstItem();
	while (c)
	{
		c->index = i;
		if (type == character)
			c->label->setText(QString("Character #%1").arg(i + 1));
		else if (type == map)
			c->label->setText(QString("Map #%1").arg(i + 1));
		c = c->next_item;
		i++;
	}
}

void Item::ImgButtonClicked()
{
	QString filename =  QFileDialog::getOpenFileName(this, tr("Open preview image"), app->applicationDirPath(), tr("PNG Images (*.png)"));
	img_edit->setText(filename);
}

void Item::ModelButtonClicked()
{
	QString filename =  QFileDialog::getOpenFileName(this, tr("Open character model"), app->applicationDirPath(), tr("OBJ Files (*.obj)"));
	model_edit->setText(filename);
}

void Item::UpdateImage()
{
	g_scene->clear();
	pixmap->load(img_edit->text());

	/*make image fit in graphics view*/
	g_scene->addPixmap(pixmap->scaled(QSize((int)g_scene->width(), (int)g_scene->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	g_view->setScene(g_scene);
}

void Item::SettingChanged()
{                                        
	parent_window->settings_saved = false;
}

