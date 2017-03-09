#ifndef ERROR_UI_H
#define ERROR_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ErrorDialog
{
	public:
	QLabel* msg_label;
	QPushButton* ok_button;

	void setupUi(QDialog* ErrorDialog)
	{
		if (ErrorDialog->objectName().isEmpty())
			ErrorDialog->setObjectName(QStringLiteral("ErrorDialog"));
		ErrorDialog->setWindowModality(Qt::ApplicationModal);
		ErrorDialog->resize(281, 174);

		msg_label = new QLabel(ErrorDialog);
		msg_label->setObjectName(QStringLiteral("msg_label"));
		msg_label->setGeometry(QRect(20, 30, 300, 16));
		ok_button = new QPushButton(ErrorDialog);
		ok_button->setObjectName(QStringLiteral("ok_button"));
		ok_button->setGeometry(QRect(80, 140, 80, 22));

		retranslateUi(ErrorDialog);
		QMetaObject::connectSlotsByName(ErrorDialog);
	}

	void retranslateUi(QDialog* ErrorDialog)
	{
		ErrorDialog->setWindowTitle(QApplication::translate("ErrorDialog", "Error", Q_NULLPTR));
		msg_label->setText(QApplication::translate("ErrorDialog", "Server Address:", Q_NULLPTR));
		ok_button->setText(QApplication::translate("ErrorDialog", "Ok", Q_NULLPTR));
	}
};

namespace Ui
{
	class ErrorDialog : public Ui_ErrorDialog {};
}

#endif // ERROR_UI_H
