#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QMap>
#include <QFile>
#include <QRegularExpression>
#include <QTextCursor>
#include <QThread>
#include <QTime>

#include <QDebug>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE











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




















#if 1
class DatabaseScanner : public QObject
{
	Q_OBJECT
private:
	QString database_filename;
	QFile english_titles;
	QFile russian_titles;

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
		database_statistics.titles_by_topic.operator[](scanned_database_items.at(DATABASE_RECORD_INDEX::TOPIC))
				<< (QStringList() << scanned_database_items.at(DATABASE_RECORD_INDEX::TITLE) << scanned_database_items.at(DATABASE_RECORD_INDEX::MD5_HASH));
		if (l == "english")
		{
			QString topic = scanned_database_items.at(DATABASE_RECORD_INDEX::TOPIC);
			if (topic.isEmpty())
				topic = "<unspecified topic>";
			english_titles.write(QString("%1::%2::%3\n")
				.arg(scanned_database_items.at(DATABASE_RECORD_INDEX::MD5_HASH))
				.arg(topic)
				.arg(scanned_database_items.at(DATABASE_RECORD_INDEX::TITLE)).toUtf8());
		}
		else if (l == "russian")
		{
			russian_titles.write(QString("%1::%2\n").arg(scanned_database_items.at(DATABASE_RECORD_INDEX::TOPIC)).arg(scanned_database_items.at(DATABASE_RECORD_INDEX::TITLE)).toUtf8());
		}

		return len + 1;
	}
public:
	DatabaseScanner(const QString database_filename) : database_filename(database_filename) {}

	struct
	{
		QMap<QString /* language */, unsigned /* count */> language_counts;
		QMap<QString /* language */, quint64 /* total size in bytes */> language_total_size;
		QMap<QString /* topic */, QList<QStringList /* title, md5 hash */>> titles_by_topic;
	}
	database_statistics;
public slots:
	void scan(void)
	{
		QFile f;
		f.setFileName(database_filename);
		if (!f.open(QFile::ReadOnly))
		{
			QMessageBox::critical(0, "Error opening database", "Can not open database file\n" + f.fileName());
			return;
		}

		english_titles.setFileName("english-titles.txt");
		if (!english_titles.open(QFile::WriteOnly))
		{
			QMessageBox::critical(0, "Error creating english output titles file", "Failed to create the output file for english book titles");
			exit(1);
		}
		russian_titles.setFileName("russian-titles.txt");
		if (!russian_titles.open(QFile::WriteOnly))
		{
			QMessageBox::critical(0, "Error creating russian output titles file", "Failed to create the output file for russian book titles");
			exit(1);
		}

		int line = 0;
		int records = 0;
		QTime timer;
		timer.start();
		QString l;
		QRegularExpression rx_value_insert(".+\\)\\s*VALUES\\s*\\(");
		while (1)
		{
			if (f.atEnd())
				break;
			line ++;
			if (!(l = f.readLine()).length())
				continue;
			if (!l.startsWith("INSERT INTO `updated`"))
				continue;
			QRegularExpressionMatch match = rx_value_insert.match(l);
			if (match.hasMatch())
			{
				int index = match.capturedEnd() - /* get back to the opening parenthesis */ 1;
				while (index < l.length()){
					if (l.at(index) == '(')
					{
						int t = scan_database_record(l, index);
						if (t == -1)
						{
							QMessageBox::critical(0, "Error parsing database record", "Failed to parse database record");
							break;
						}
						records ++;
						index += t;
					}
					else
						index ++;
				}
			}
			if (line && !(line % 100))
			{
				qDebug() << line << "lines read, records found:" << records << "time elapsed (ms):" << timer.elapsed();
				timer.restart();
			}
		}

		qDebug() << "---------------------------------------------";
		qDebug() << line << "lines read";
		qDebug() << "records found:" << records;
		QStringList languages = QStringList()
				<< "bulgarian" << "russian" << "english" << /* unspecified language */"";
		for (const auto & l : languages)
			qDebug().noquote() << (l.isEmpty() ? "unspecified language" : l) << "books found:" << database_statistics.language_counts.operator[](l) << "total size:" << ((double) database_statistics.language_total_size.operator[](l)) / 1.e12 << "terabytes";

		english_titles.close();
		russian_titles.close();
	}
};
#endif

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	QFile english_titles;
	QFile russian_titles;
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
		QMap<QString /* topic */, QList<QStringList /* title, md5 hash */>> titles_by_topic;
	}
	database_statistics;
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
		database_statistics.titles_by_topic.operator[](scanned_database_items.at(DATABASE_RECORD_INDEX::TOPIC))
				<< (QStringList() << scanned_database_items.at(DATABASE_RECORD_INDEX::TITLE) << scanned_database_items.at(DATABASE_RECORD_INDEX::MD5_HASH));
		if (l == "english")
		{
			QString topic = scanned_database_items.at(DATABASE_RECORD_INDEX::TOPIC);
			if (topic.isEmpty())
				topic = "<unspecified topic>";
			english_titles.write(QString("%1::%2::%3\n")
				.arg(scanned_database_items.at(DATABASE_RECORD_INDEX::MD5_HASH))
				.arg(topic)
				.arg(scanned_database_items.at(DATABASE_RECORD_INDEX::TITLE)).toUtf8());
		}
		else if (l == "russian")
		{
			russian_titles.write(QString("%1::%2\n").arg(scanned_database_items.at(DATABASE_RECORD_INDEX::TOPIC)).arg(scanned_database_items.at(DATABASE_RECORD_INDEX::TITLE)).toUtf8());
		}

		return len + 1;
	}

	int get_selected_topic(void)
	{
		int topic = 0;
		for (const auto & c : ui->plainTextEditTopics->textCursor().selectedText())
		{
			if (!c.isDigit())
				break;
			topic = topic * 10 + c.digitValue();
		}
		return topic;
	}

	void populate_topic_list(void)
	{
		QRegularExpression rx("\\((\\d+),'([^']*)'");
		QFile f(":/resources/topics.txt");
		f.open(QFile::ReadOnly);
		QString line;
		ui->plainTextEditTopics->clear();
		while (!f.atEnd())
		{
			line = f.readLine();
			QRegularExpressionMatch match = rx.match(line);
			if (match.hasMatch())
				ui->plainTextEditTopics->appendPlainText(QString("%1::%2").arg(match.captured(1)).arg(match.captured(2)));
		}
		QTextCursor c(ui->plainTextEditTopics->textCursor());
		c.movePosition(QTextCursor::Start);
		ui->plainTextEditTopics->setTextCursor(c);
	}
};
