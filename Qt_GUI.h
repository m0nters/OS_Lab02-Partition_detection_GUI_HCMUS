#ifndef QT_GUI_H
#define QT_GUI_H
#pragma once

#include "ui_Qt_GUI.h"
#include <QtWidgets/QMainWindow>
#include <QKeyEvent>
#include <set>


class Qt_GUI : public QMainWindow
{
	Q_OBJECT

public:
	Qt_GUI(QWidget* parent = nullptr);
	~Qt_GUI();
	Ui::Qt_GUIClass* getUi() { return &ui; }

	QTreeWidget* get_current_treeWidget() {
		return ui.treeWidget;
	}

	void QTreeWidgetItem_populate_info(QTreeWidgetItem*& node, QString name, QString date_created, QString time_created, QString total_size, QString attributes);

	// STORED POINTERS FOR DELETE AND RECOVER IN THE CURRENT SESSION
	QTreeWidgetItem* selectedItem = nullptr; // for delete
	QTreeWidgetItem* parent_selectedItem = nullptr; // for delete above node from GUI tree
	std::map<std::pair<int, std::string>, std::pair<QTreeWidgetItem*, QTreeWidgetItem*>> deleted_map; // map {ith_drive, file_name} -> {node A that contains it, A's parent}

	// FOR SHOWING/HIDING SYSTEM FILES
	std::vector< std::pair<QTreeWidgetItem*, QTreeWidgetItem*> > system_files; // store a list of `drive`s, in each `drive` stores a list of `pair<system files node, node's parent>`s

public slots:
	void onTreeItemClicked(QTreeWidgetItem* item, int column); // left click to .txt file to show its content
	void resizeColumnsToContents(); // auto resize columns width when expand/collapse folders
	void on_delete_button_clicked(); // delete selected file/folder
	void on_restore_button_clicked(); // restore selected file/folder
	void onDriveOrFileNameChanged(); // enable restore_button condition
	void onShowSystemFilesStateChanged(int state); // checkbox show system files

protected:
	void keyPressEvent(QKeyEvent* event) override; // Override keyPressEvent method
	void mousePressEvent(QMouseEvent* event) override;

private:
	Ui::Qt_GUIClass ui;
};
#endif