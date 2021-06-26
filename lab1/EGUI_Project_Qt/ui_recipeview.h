/********************************************************************************
** Form generated from reading UI file 'recipeview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECIPEVIEW_H
#define UI_RECIPEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RecipeView
{
public:
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *productName;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QPlainTextEdit *productDesc;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QTableView *productView;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QLineEdit *ingredientName;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QLineEdit *ingredientNr;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_6;
    QLineEdit *ingredientUnit;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSave;
    QPushButton *btnCancel;

    void setupUi(QDialog *RecipeView)
    {
        if (RecipeView->objectName().isEmpty())
            RecipeView->setObjectName(QStringLiteral("RecipeView"));
        RecipeView->resize(568, 670);
        verticalLayout_7 = new QVBoxLayout(RecipeView);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(RecipeView);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        productName = new QLineEdit(RecipeView);
        productName->setObjectName(QStringLiteral("productName"));

        horizontalLayout->addWidget(productName);


        verticalLayout_7->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(RecipeView);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        productDesc = new QPlainTextEdit(RecipeView);
        productDesc->setObjectName(QStringLiteral("productDesc"));

        verticalLayout->addWidget(productDesc);


        verticalLayout_7->addLayout(verticalLayout);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(RecipeView);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_6->addLayout(verticalLayout_2);

        productView = new QTableView(RecipeView);
        productView->setObjectName(QStringLiteral("productView"));

        verticalLayout_6->addWidget(productView);


        verticalLayout_7->addLayout(verticalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_4 = new QLabel(RecipeView);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_3->addWidget(label_4);

        ingredientName = new QLineEdit(RecipeView);
        ingredientName->setObjectName(QStringLiteral("ingredientName"));

        verticalLayout_3->addWidget(ingredientName);


        horizontalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_5 = new QLabel(RecipeView);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_4->addWidget(label_5);

        ingredientNr = new QLineEdit(RecipeView);
        ingredientNr->setObjectName(QStringLiteral("ingredientNr"));

        verticalLayout_4->addWidget(ingredientNr);


        horizontalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_6 = new QLabel(RecipeView);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_5->addWidget(label_6);

        ingredientUnit = new QLineEdit(RecipeView);
        ingredientUnit->setObjectName(QStringLiteral("ingredientUnit"));

        verticalLayout_5->addWidget(ingredientUnit);


        horizontalLayout_6->addLayout(verticalLayout_5);


        horizontalLayout_7->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        btnAdd = new QPushButton(RecipeView);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));

        horizontalLayout_5->addWidget(btnAdd);

        btnDelete = new QPushButton(RecipeView);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));

        horizontalLayout_5->addWidget(btnDelete);


        horizontalLayout_7->addLayout(horizontalLayout_5);


        verticalLayout_7->addLayout(horizontalLayout_7);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_7->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        btnSave = new QPushButton(RecipeView);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        horizontalLayout_4->addWidget(btnSave);

        btnCancel = new QPushButton(RecipeView);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout_4->addWidget(btnCancel);


        verticalLayout_7->addLayout(horizontalLayout_4);


        retranslateUi(RecipeView);

        QMetaObject::connectSlotsByName(RecipeView);
    } // setupUi

    void retranslateUi(QDialog *RecipeView)
    {
        RecipeView->setWindowTitle(QApplication::translate("RecipeView", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("RecipeView", "Product name", Q_NULLPTR));
        productName->setText(QString());
        label_2->setText(QApplication::translate("RecipeView", "Description", Q_NULLPTR));
        label_3->setText(QApplication::translate("RecipeView", "Ingredients", Q_NULLPTR));
        label_4->setText(QApplication::translate("RecipeView", "Ingredient name", Q_NULLPTR));
        label_5->setText(QApplication::translate("RecipeView", "Number", Q_NULLPTR));
        label_6->setText(QApplication::translate("RecipeView", "Unit", Q_NULLPTR));
        btnAdd->setText(QApplication::translate("RecipeView", "Add ingredient", Q_NULLPTR));
        btnDelete->setText(QApplication::translate("RecipeView", "Delete", Q_NULLPTR));
        btnSave->setText(QApplication::translate("RecipeView", "Save recipe", Q_NULLPTR));
        btnCancel->setText(QApplication::translate("RecipeView", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RecipeView: public Ui_RecipeView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECIPEVIEW_H
