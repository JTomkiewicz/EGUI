/********************************************************************************
** Form generated from reading UI file 'basketofrecipesview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASKETOFRECIPESVIEW_H
#define UI_BASKETOFRECIPESVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BasketOfRecipesView
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelAvailableRecipes;
    QSpacerItem *horizontalSpacer;
    QTableView *tableViewAvailable;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelChosenRecipes;
    QSpacerItem *horizontalSpacer_2;
    QTableView *tableViewChosen;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QPlainTextEdit *txtNeededIngredients;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnClose;

    void setupUi(QDialog *BasketOfRecipesView)
    {
        if (BasketOfRecipesView->objectName().isEmpty())
            BasketOfRecipesView->setObjectName(QStringLiteral("BasketOfRecipesView"));
        BasketOfRecipesView->resize(692, 550);
        verticalLayout_5 = new QVBoxLayout(BasketOfRecipesView);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelAvailableRecipes = new QLabel(BasketOfRecipesView);
        labelAvailableRecipes->setObjectName(QStringLiteral("labelAvailableRecipes"));

        horizontalLayout->addWidget(labelAvailableRecipes);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tableViewAvailable = new QTableView(BasketOfRecipesView);
        tableViewAvailable->setObjectName(QStringLiteral("tableViewAvailable"));

        verticalLayout->addWidget(tableViewAvailable);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        btnAdd = new QPushButton(BasketOfRecipesView);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));

        verticalLayout_3->addWidget(btnAdd);

        btnDelete = new QPushButton(BasketOfRecipesView);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));

        verticalLayout_3->addWidget(btnDelete);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelChosenRecipes = new QLabel(BasketOfRecipesView);
        labelChosenRecipes->setObjectName(QStringLiteral("labelChosenRecipes"));

        horizontalLayout_2->addWidget(labelChosenRecipes);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        tableViewChosen = new QTableView(BasketOfRecipesView);
        tableViewChosen->setObjectName(QStringLiteral("tableViewChosen"));

        verticalLayout_2->addWidget(tableViewChosen);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_5->addLayout(horizontalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(BasketOfRecipesView);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_4);

        txtNeededIngredients = new QPlainTextEdit(BasketOfRecipesView);
        txtNeededIngredients->setObjectName(QStringLiteral("txtNeededIngredients"));
        txtNeededIngredients->setReadOnly(true);

        verticalLayout_4->addWidget(txtNeededIngredients);


        verticalLayout_5->addLayout(verticalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        btnClose = new QPushButton(BasketOfRecipesView);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout_5->addWidget(btnClose);


        verticalLayout_5->addLayout(horizontalLayout_5);


        retranslateUi(BasketOfRecipesView);

        QMetaObject::connectSlotsByName(BasketOfRecipesView);
    } // setupUi

    void retranslateUi(QDialog *BasketOfRecipesView)
    {
        BasketOfRecipesView->setWindowTitle(QApplication::translate("BasketOfRecipesView", "Dialog", Q_NULLPTR));
        labelAvailableRecipes->setText(QApplication::translate("BasketOfRecipesView", "Available recipes", Q_NULLPTR));
        btnAdd->setText(QApplication::translate("BasketOfRecipesView", "->", Q_NULLPTR));
        btnDelete->setText(QApplication::translate("BasketOfRecipesView", "<-", Q_NULLPTR));
        labelChosenRecipes->setText(QApplication::translate("BasketOfRecipesView", "Chosen recipes", Q_NULLPTR));
        label_3->setText(QApplication::translate("BasketOfRecipesView", "Needed ingredients", Q_NULLPTR));
        btnClose->setText(QApplication::translate("BasketOfRecipesView", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BasketOfRecipesView: public Ui_BasketOfRecipesView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASKETOFRECIPESVIEW_H
