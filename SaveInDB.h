#ifndef SAVEINDB_H_INCLUDED
#define SAVEINDB_H_INCLUDED
#include <sqlite3.h>
#include <string>
#include <wx/vector.h>
#include <wx/string.h>
#include <cassert>

struct SaveInDB {

    explicit SaveInDB(const std::string & = "chat_data.sqlite3");
    ~SaveInDB();

    void SetMessage(wxString const &);
    wxString GetMessage() const;
    void WriteMessageInDB();
    void ReadMessageInDB();
    const wxVector<wxString> & GetAllMessage() const;

    private:

    sqlite3 * m_ptrdb;
    wxString m_message;
    wxVector<wxString> m_allmessages;
};

#endif // SAVEINDB_H_INCLUDED
