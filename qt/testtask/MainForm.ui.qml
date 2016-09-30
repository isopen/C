import QtQuick 2.5
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.3
import QtQuick.LocalStorage 2.0
import "utils.js" as UtilsPhoneBook

RowLayout {

    Rectangle {

        Layout.fillWidth: true
        Layout.minimumWidth: 100
        Layout.preferredWidth: 200
        Layout.preferredHeight: parent.height

        ScrollView {

            width: parent.width
            height: parent.height

            ListView {

                id: list_view_phone_book
                clip: true
                model: PhoneBookModel { id: phoneBookModel }

                delegate: Rectangle {

                    property int indexOfThisDelegate: index
                    id: element_phone_book
                    height: 50
                    width: parent.width

                    TextField {
                        id: fio_input_phone_book
                        width: (parent.width - edit_button.width - remove_button.width - number_input_phone_book.width)
                        text: name
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    TextField {
                        id: number_input_phone_book
                        anchors { left : fio_input_phone_book.right; top : fio_input_phone_book.top}
                        width: 100
                        text: number
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                        validator: RegExpValidator{regExp: /\d+/}
                        maximumLength: 11
                    }

                    Button {
                        id: edit_button
                        anchors { left : number_input_phone_book.right; top : number_input_phone_book.top}
                        text: "Изменить"
                        enabled: true
                        onClicked: {
                            UtilsPhoneBook.updatePhone(id, parent.indexOfThisDelegate, {name: fio_input_phone_book.text, phone: number_input_phone_book.text});
                        }
                    }

                    Button {
                        id: remove_button
                        anchors { left : edit_button.right; top : edit_button.top}
                        text: "Удалить"
                        enabled: true
                        onClicked: {
                            UtilsPhoneBook.removePhone(id, parent.indexOfThisDelegate);
                        }
                    }
                }
            }
        }

    }

    Rectangle {

        Layout.fillWidth: true
        Layout.minimumWidth: 50
        Layout.preferredWidth: 100
        Layout.maximumWidth: 300
        Layout.preferredHeight: parent.height

        ColumnLayout {

            spacing: 5

            TextField {
                id: search_name_phone_book
                placeholderText: qsTr("Имя")
            }

            TextField {
                id: search_number_phone_book
                placeholderText: qsTr("Телефон")
                validator: RegExpValidator{regExp: /\d+/}
                maximumLength: 11
            }

            Button {
                text: "Поиск"
                width: parent.width
                onClicked: {
                    UtilsPhoneBook.searchPhone({name: search_name_phone_book.text, phone: search_number_phone_book.text});
                 }
            }

            TextField {
                id: username
                placeholderText: qsTr("ФИО")
                maximumLength: 100
            }

            TextField {
                id: phone
                placeholderText: qsTr("Телефон")
                validator: RegExpValidator{regExp: /\d+/}
                maximumLength: 11
            }

            Button {

                id: add_phone
                text: "Добавить"
                width: parent.width

                onClicked: {
                    UtilsPhoneBook.insertPhone({name: username.text, phone: phone.text});
                 }
            }

        }
    }

    Component.onCompleted: {
        UtilsPhoneBook.initDB(phoneBookModel);
    }

}
