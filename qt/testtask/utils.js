var db = LocalStorage.openDatabaseSync("PhoneBookDB0.2", "1.0", "The PhoneBookDB!", 1000000);

function initDB() {
    db.transaction(
        function(tx) {
            tx.executeSql('create table if not exists Phonebook(id integer primary key autoincrement not null, name varchar(100), phone integer)');
            var rs = tx.executeSql('select * from Phonebook order by id desc;');
            for(var i = 0; i < rs.rows.length; i++) {
                phoneBookModel.insert(i, {id: rs.rows.item(i).id, name: rs.rows.item(i).name, number: rs.rows.item(i).phone*1});
             }
        }
    )

}

function insertPhone(data) {
    if(data.name != '' && data.name != '') {
        db.transaction(
            function(tx) {
                var rs = tx.executeSql('select * from Phonebook where name = ? and phone = ?', [ data.name, data.phone ]);
                if(rs.rows.length == 0) {
                    rs = tx.executeSql('insert into Phonebook (name, phone) values(?, ?)', [ data.name, data.phone ]);
                    phoneBookModel.insert(0, {id: (rs.insertId*1), name: data.name, number: (data.phone*1)});
                    list_view_phone_book.model = phoneBookModel;
                }else {
                    console.log('Запись уже существует в телефонной книге');
                }
            }
        );
    }else {
        console.log('Неверный ввод в поле "фио" или "телефон"');
    }
}

function searchPhone(data) {
    if(data.name != '' || data.phone != '') {
        db.transaction(
            function(tx) {
                var rs = tx.executeSql('select * from Phonebook where name = ? or phone = ? order by name desc;', [ data.name, data.phone ]),
                    c = rs.rows.length;
                if(c > 0) {
                    phoneBookModel.clear();
                    for(var i = 0; i < c; i++) {
                        phoneBookModel.insert(i, {id: rs.rows.item(i).id, name: rs.rows.item(i).name, number: rs.rows.item(i).phone*1});
                    }
                }else {
                    console.log('Нет результатов по Вашему запросу');
                }
            }
        );
    }else {
        phoneBookModel.clear();
        initDB();
    }
}

function updatePhone(id, index, data) {
    if(data.name != '' && data.phone != '') {
        db.transaction(
            function(tx) {
                tx.executeSql('update Phonebook set name = ? , phone = ? where id = ?',[ data.name, data.phone, id ]);
                phoneBookModel.set(index, {id: phoneBookModel.get(index).id, name: data.name, number: data.phone*1})
                list_view_phone_book.model = phoneBookModel;
            }
        );
    }else {
        console.log('Неверный ввод в поле "фио" или "телефон"');
    }
}

function removePhone(id, index) {
    db.transaction(
        function(tx) {
            var rs = tx.executeSql('delete from Phonebook where id = ?',[ id ]);
            phoneBookModel.remove(index);
            if(phoneBookModel.count > 0) {
                list_view_phone_book.model = phoneBookModel;
            }else {
                console.log('Список оказался пустым после удаления');
                initDB();
            }
        }
    );
}
