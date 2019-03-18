#include "SaveInDB.h"

SaveInDB::SaveInDB(std::string const & name_database){
    using std::string;
    auto result = sqlite3_open_v2(name_database.c_str(), &m_ptrdb,
                            SQLITE_OPEN_CREATE|SQLITE_OPEN_READWRITE, nullptr);
    if(result != SQLITE_OK){
        wxMessageBox(wxString(sqlite3_errmsg(m_ptrdb)));
        return;
    }

    sqlite3_stmt * stmt = nullptr;
    string request_sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='list_messages';";
    result = sqlite3_prepare_v2(m_ptrdb, request_sql.c_str(),
                                request_sql.size()+1, &stmt, nullptr);

    //assert(result == SQLITE_OK);
    result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if(result == SQLITE_DONE) {
            request_sql.clear();
            request_sql = "CREATE TABLE list_messages("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "message TEXT NOT NULL);";
            result = sqlite3_prepare_v2(m_ptrdb, request_sql.c_str(),
                                         request_sql.size()+1, &stmt, nullptr);
      //      assert(result == SQLITE_OK);
            result = sqlite3_step(stmt);
        //    assert(result == SQLITE_DONE);
            sqlite3_finalize(stmt);
    }
}

SaveInDB::~SaveInDB(){
    sqlite3_close(m_ptrdb);
}

void SaveInDB::SetMessage(std::string const & msg){
    m_message = msg;
}

std::string SaveInDB::GetMessage() const {
    return m_message;
}

void SaveInDB::WriteMessageInDB(){
    sqlite3_stmt * stmt = nullptr;
    std::string request_sql = "INSERT INTO list_messages(message) VALUES(:message);";
    auto result = sqlite3_prepare_v2(m_ptrdb, request_sql.c_str(),
                                     request_sql.size()+1, &stmt, nullptr);
    //assert(result == SQLITE_OK);
    auto index = sqlite3_bind_parameter_index(stmt, ":message");
    result = sqlite3_bind_text(stmt, index, m_message.c_str(),
                               m_message.size()+1, SQLITE_TRANSIENT);
    //assert(result == SQLITE_OK);
    result = sqlite3_step(stmt);
    //assert(result == SQLITE_DONE);
    sqlite3_finalize(stmt);
    //wxMessageBox(m_message);
}

void SaveInDB::ReadMessageInDB(){
    m_allmessages.clear();
    sqlite3_stmt * stmt = nullptr;
    std::string request_sql = "SELECT message FROM list_messages;";
    auto result = sqlite3_prepare_v2(m_ptrdb, request_sql.c_str(),
                                      request_sql.size()+1, &stmt, nullptr);
    while((result = sqlite3_step(stmt)) == SQLITE_ROW){
        m_allmessages.push_back(wxString((const char*)sqlite3_column_text(stmt,0), wxConvUTF8));
    }
    //assert(result == SQLITE_DONE);
    sqlite3_finalize(stmt);
}

const wxVector<wxString> & SaveInDB::GetAllMessage() const{
    return m_allmessages;
}
