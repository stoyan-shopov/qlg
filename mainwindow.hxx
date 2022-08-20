#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QMap>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	int scan_number(const QString & data, int offset)
	{
		int len = 0;
		while (offset < data.length() && data.at(offset).isDigit())
			len ++, offset ++;
		if (!len)
			return -1;
		return len;
	}
	int scan_string(const QString & data, int offset)
	{
		int len = 0;
		if (offset < data.length() && data.at(offset) != '\'')
			return -1;
		len ++, offset ++;
		while (offset < data.length() && data.at(offset) != '\'')
		{
			/* handle escaped characters */
			if (data.at(offset) == '\\')
			{
				len ++, offset ++;
				if (offset == data.length())
					return -1;
			}
			len ++, offset ++;
		}
		if (offset < data.length() && data.at(offset) == '\'')
			return len + 1;
		return -1;
	}
	struct
	{
		QMap<QString /* language */, unsigned /* count */> language_counts;
		QMap<QString /* language */, quint64 /* total size in bytes */> language_total_size;
	}
	database_statistics;
	enum
	{
		/* Expected number of records in the database entry. */
		DATABASE_RECORD_COUNT		= 47,
	};
	enum DATABASE_RECORD_INDEX
	{
		ID,				/* id */
		TITLE,				/* title */
		VOLUME_INFO,			/* volume info */
		SERIES,				/* series */
		PERIODICAL,			/* periodical */
		AUTHOR,				/* author */
		YEAR,				/* year */
		EDITION,			/* edition */
		PUBLISHER,			/* publisher */
		CITY,				/* city */
		PAGES,				/* pages */
		PAGES_IN_FILE,			/* pages in file */
		LANGUAGE,			/* language */
		TOPIC,				/* topic */
		LIBRARY,			/* library */
		ISSUE,				/* issue */
		IDENTIFIER,			/* identifier */
		ISSN,				/* issn */
		ASIN,				/* asin */
		UDC,				/* udc */
		LBC,				/* lbc */
		DDC,				/* ddc */
		LCC,				/* lcc */
		DOI,				/* doi */
		GOOGLE_BOOK_ID,			/* google book id */
		OPEN_LIBRARY_ID,		/* open library id */
		COMMENTARY,			/* commentary */
		DPI,				/* dpi */
		COLOR,				/* color */
		CLEANED,			/* cleaned */
		ORIENTATION,			/* orientation */
		PAGINATED,			/* paginated */
		SCANNED,			/* scanned */
		BOOKMARKED,			/* bookmarked */
		SEARCHABLE,			/* searchable */
		FILE_SIZE,			/* file size */
		FILE_NAME_EXTENSION,		/* file name extension */
		MD5_HASH,			/* md5 hash */
		GENERIC,			/* generic */
		VISIBLE,			/* visible */
		LOCATOR,			/* locator */
		LOCAL,				/* local */
		TIME_ADDED,			/* time added */
		TIME_LAST_MODIFIED,		/* time last modified */
		COVER_URL,			/* cover url */
		TAGS,				/* tags */
		IDENTIFIER_WITHOUT_DASHES,	/* identifier without dashes */
	};
	const struct database_item
	{
		enum
		{
			INVALID		= 0,
			NUMBER,
			STRING,
		}
		type;
	}
	database_items[DATABASE_RECORD_COUNT] =
		{
			{ .type = database_item::NUMBER, }, //"(\\d+),"		/* id */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* title */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* volume info */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* series */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* periodical */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* author */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* year */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* edition */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* publisher */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* city */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* pages */
			{ .type = database_item::NUMBER, }, //"(\\d+),"		/* pages in file */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* language */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* topic */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* library */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* issue */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* identifier */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* issn */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* asin */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* udc */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* lbc */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* ddc */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* lcc */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* doi */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* google book id */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* open library id */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* commentary */
			{ .type = database_item::NUMBER, }, //"(\\d+),"		/* dpi */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* color */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* cleaned */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* orientation */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* paginated */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* scanned */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* bookmarked */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* searchable */
			{ .type = database_item::NUMBER, }, //"(\\d+),"		/* file size */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* file name extension */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* md5 hash */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* generic */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* visible */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* locator */
			{ .type = database_item::NUMBER, }, //"(\\d+),"		/* local */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* time added */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* time last modified */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* cover url */
			{ .type = database_item::STRING, }, //"'([^']*)',"	/* tags */
			{ .type = database_item::STRING, }, //"'([^']*)'"	/* identifier without dashes */
		};
	int scan_database_record(const QString & data, int offset) {
		int len = 0;
		if (offset < data.length() && data.at(offset) != '\(')
			return -1;
		len ++, offset ++;
		int t;
		QStringList scanned_database_items;
		for (const auto & item : database_items)
		{
			switch (item.type)
			{
				default: QMessageBox::critical(0, "Unknown database item type", "Database item type unrecognized; aborting"); return -1;
				case database_item::NUMBER:
					t = scan_number(data, offset);
					if (t == -1)
					{
						qDebug() << "database record is:" << data.mid(offset - len, 100);
						QMessageBox::critical(0, "Error scanning a number item", "Expected a number item, but the scan fails; aborting"); return -1;
					}
					scanned_database_items << data.mid(offset, t);
				break;
				case database_item::STRING:
					t = scan_string(data, offset);
					if (t == -1)
					{
						qDebug() << "database record is:" << data.mid(offset - len, 100);
						QMessageBox::critical(0, "Error scanning a string item", "Expected a string item, but the scan fails; aborting"); return -1;
					}
					scanned_database_items << data.mid(offset + 1, t - 2);
				break;
			}
			len += t, offset += t;
			/* HACK */
			if (offset < data.length() && data.at(offset) == ',')
				len ++, offset ++;
		}

		if (scanned_database_items.length() != DATABASE_RECORD_COUNT)
		{
			QMessageBox::critical(0, "Bad database entry record count", "Unexpected number of database records found in database entry"); return -1;
		}
		if (offset < data.length() && data.at(offset) != ')')
			return -1;

		QString l(scanned_database_items.at(DATABASE_RECORD_INDEX::LANGUAGE).toLower());
		bool flag;
		unsigned size = scanned_database_items.at(DATABASE_RECORD_INDEX::FILE_SIZE).toUInt(& flag);
		if (!flag)
		{
			QMessageBox::critical(0, "Bad file size value", "Could not decode file size value in database entry"); return -1;
		}

		database_statistics.language_counts.operator[](l) ++;
		database_statistics.language_total_size.operator[](l) += size;

		return len + 1;
	}
};
