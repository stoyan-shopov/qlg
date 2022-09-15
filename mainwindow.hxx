#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QMap>
#include <QFile>
#include <QRegularExpression>
#include <QTextCursor>
#include <QThread>
#include <QElapsedTimer>
#include <QSharedPointer>

#include <QDebug>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum
{
	/* Expected number of records in the database entry. */
	DATABASE_RECORD_COUNT		= 47,
	/* Number of threads used for scanning the database. */
	NR_DATABASE_SCANNER_THREADS	= 2,
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

class DatabaseScannerWorker : public QThread
{
	Q_OBJECT
private:

	const QList<QByteArray> & lines;
	const int start_line, line_stride;

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
		QSharedPointer<QStringList> scanned_database_items(new QStringList);
		for (const auto & item : database_items)
		{
			switch (item.type)
			{
				default: QMessageBox::critical(0, "Unknown database item type", "Database item type unrecognized; aborting"); return -1;
				case database_item::NUMBER:
					t = scan_number(data, offset);
					if (t == -1)
					{
						emit error("Unrecognized database record: " + data.mid(offset - len, 100));
						QMessageBox::critical(0, "Error scanning a number item", "Expected a number item, but the scan fails; aborting"); return -1;
					}
					* scanned_database_items << data.mid(offset, t);
				break;
				case database_item::STRING:
					t = scan_string(data, offset);
					if (t == -1)
					{
						emit error("Unrecognized database record: " + data.mid(offset - len, 100));
						QMessageBox::critical(0, "Error scanning a string item", "Expected a string item, but the scan fails; aborting"); return -1;
					}
					* scanned_database_items << data.mid(offset + 1, t - 2);
				break;
			}
			len += t, offset += t;
			/* HACK */
			if (offset < data.length() && data.at(offset) == ',')
				len ++, offset ++;
		}

		if ((* scanned_database_items).length() != DATABASE_RECORD_COUNT)
		{
			QMessageBox::critical(0, "Bad database entry record count", "Unexpected number of database records found in database entry"); return -1;
		}
		if (offset < data.length() && data.at(offset) != ')')
			return -1;

		QString l((* scanned_database_items).at(DATABASE_RECORD_INDEX::LANGUAGE).toLower());
		titles << scanned_database_items;
		return len + 1;
	}
public:
	/* This is a list of all titles. All database records have their fields, including numerical fields, stored as lists of strings. */
	QVector<QSharedPointer<QStringList>> titles;
	DatabaseScannerWorker(const QList<QByteArray> & lines, const int start_line, const int line_stride) : lines(lines), start_line(start_line), line_stride(line_stride) {}
	void run(void) override
	{
		int line_nr;
		int records = 0;
		QRegularExpression rx_value_insert(".+\\)\\s*VALUES\\s*\\(");
		for (line_nr = start_line; line_nr < lines.length(); line_nr += line_stride)
		{
			QString l = lines.at(line_nr);
			if (!l.length())
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
							break;
						}
						records ++;
						index += t;
					}
					else
						index ++;
				}
			}
		}
	}
signals:
	void error(const QString error_message);
};

class DatabaseScanner : public QObject
{
	Q_OBJECT
private:
	QString database_filename;
	QFile english_titles;
	QFile russian_titles;
	QFile titles_by_id;
	QFile titles_by_size;

	QString * empty_string = new QString();

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
		QSharedPointer<QList<QString *>> scanned_database_items(new QList<QString *>(DATABASE_RECORD_COUNT));
		int record_index = 0;
		for (const auto & item : database_items)
		{
			int start, xlen;
			switch (item.type)
			{
				default: QMessageBox::critical(0, "Unknown database item type", "Database item type unrecognized; aborting"); return -1;
				case database_item::NUMBER:
					t = scan_number(data, offset);
					if (t == -1)
						return -1;
					start = offset, xlen = t;
				break;
				case database_item::STRING:
					t = scan_string(data, offset);
					if (t == -1)
						return -1;
					start = offset + 1, xlen = t - 2;
				break;
			}
			if (!xlen)
			{
				database_statistics.total_empty_records ++;
				scanned_database_items->operator[](record_index) = empty_string;
			}
			else
			{
				scanned_database_items->operator[](record_index) = new QString(data.mid(start, xlen));
			}
			record_index ++;
			database_statistics.total_records ++;
			len += t, offset += t;
			/* HACK */
			if (offset < data.length() && data.at(offset) == ',')
				len ++, offset ++;
		}

		if (scanned_database_items->length() != DATABASE_RECORD_COUNT)
		{
			QMessageBox::critical(0, "Bad database entry record count", "Unexpected number of database records found in database entry"); return -1;
		}
		if (offset < data.length() && data.at(offset) != ')')
			return -1;

		QString l(scanned_database_items->at(DATABASE_RECORD_INDEX::LANGUAGE)->toLower());
		bool flag;
		unsigned size = scanned_database_items->at(DATABASE_RECORD_INDEX::FILE_SIZE)->toUInt(& flag);
		if (!flag)
		{
			QMessageBox::critical(0, "Bad file size value", "Could not decode file size value in database entry"); return -1;
		}

		database_statistics.total_byte_size += size;
		database_statistics.language_counts.operator[](l) ++;
		database_statistics.language_total_size.operator[](l) += size;
#if 0
		database_statistics.titles_by_topic.operator[]((* scanned_database_items).at(DATABASE_RECORD_INDEX::TOPIC))
				<< (QStringList() << (* scanned_database_items).at(DATABASE_RECORD_INDEX::TITLE) << (* scanned_database_items).at(DATABASE_RECORD_INDEX::MD5_HASH));
#endif
		database_statistics.titles << scanned_database_items;
		return len + 1;
	}
public:
	DatabaseScanner(const QString database_filename) : database_filename(database_filename) {}

	struct
	{
		QMap<QString /* language */, unsigned /* count */> language_counts;
		QMap<QString /* language */, quint64 /* total size in bytes */> language_total_size;
		QMap<QString /* topic */, QList<QStringList /* title, md5 hash */>> titles_by_topic;
		quint64 total_byte_size;
		quint64 total_empty_records = 0;
		quint64 total_records = 0;

		/* This is a list of all titles. All database records have their fields, including numerical fields, stored as lists of strings. */
		QVector<QSharedPointer<QList<QString *>>> titles;
	}
	database_statistics;
signals:
	void error(const QString error_message);
	void message(const QString message);
	void done(void);
public slots:
	void scan(void)
	{
		QFile f;
		f.setFileName(database_filename);
		if (!f.open(QFile::ReadOnly))
		{
			QString error_message = "Can not open database file\n" + f.fileName();
			emit error(error_message);
			return;
		}

		english_titles.setFileName("english-titles.txt");
		if (!english_titles.open(QFile::WriteOnly))
		{
			QString error_message = "Failed to create the output file for english book titles";
			emit error(error_message);
			return;
		}
		russian_titles.setFileName("russian-titles.txt");
		if (!russian_titles.open(QFile::WriteOnly))
		{
			QString error_message = "Failed to create the output file for russian book titles";
			emit error(error_message);
			return;
		}

		titles_by_id.setFileName("titles-by-id.txt");
		if (!titles_by_id.open(QFile::WriteOnly))
		{
			QString error_message = "Failed to create the output file for titles-by-id";
			emit error(error_message);
			return;
		}
		titles_by_size.setFileName("titles-by-size.txt");
		if (!titles_by_size.open(QFile::WriteOnly))
		{
			QString error_message = "Failed to create the output file for titles-by-size";
			emit error(error_message);
			return;
		}

		int line = 0;
		int records = 0;
		QElapsedTimer timer, total_timer;
		timer.start();
		total_timer.start();
		QString l;
		QRegularExpression rx_value_insert(".+\\)\\s*VALUES\\s*\\(");
		database_statistics.total_byte_size = 0;
		QList<QByteArray> lines;
		{
			QByteArray data = f.readAll();
			emit message(QString("Reading the database took %1 milliseconds.").arg(timer.elapsed()));
			/* TODO: this may be wrong for utf8 encoding. */
			timer.restart();
			lines = data.split('\n');
		}
		emit message(QString("Splitting the database contents into lines took %1 milliseconds.").arg(timer.elapsed()));
		timer.restart();
		while (lines.length())
		{
			l = lines.front();
			lines.pop_front();
			line ++;
			if (!l.length())
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
							break;
						records ++;
						index += t;
					}
					else
						index ++;
				}
			}
			if (line && !(line % 100))
			{
				emit message(QString("%1 lines read, records found: %2; time elapsed (ms): %3").arg(line).arg(records).arg(timer.elapsed()));
				qDebug() << QString("%1 lines read, records found: %2; time elapsed (ms): %3").arg(line).arg(records).arg(timer.elapsed());
				timer.restart();
			}
		}

		emit message("---------------------------------------------");
		emit message(QString("%1 lines read").arg(line));
		emit message(QString("%1 records found").arg(records));
		QStringList languages = QStringList()
				<< "bulgarian" << "russian" << "english" << /* unspecified language */"";
		for (const auto & l : languages)
		{
			emit message(QString("%1 books found: %2; total size: %3 terabytes")
				     .arg(l.isEmpty() ? "unspecified language" : l)
				     .arg(database_statistics.language_counts.operator[](l))
					.arg(((double) database_statistics.language_total_size.operator[](l)) / 1.e12));
		}

		english_titles.close();
		russian_titles.close();
		titles_by_id.close();
		titles_by_size.close();

		qDebug() << "total library size:" << (((double) database_statistics.total_byte_size) / 1.e12) << "terabytes";
		emit message(QString("Percentage of empty records: %1").arg(((double) database_statistics.total_empty_records / database_statistics.total_records) * 100));
		emit message(QString("Total database processing time: %1 milliseconds.").arg(total_timer.elapsed()));
		emit done();
	}

	void scan_new_all_data_without_split(void)
	{
		QFile f;
		f.setFileName(database_filename);
		if (!f.open(QFile::ReadOnly))
		{
			QString error_message = "Can not open database file\n" + f.fileName();
	    //QMessageBox::critical(0, "Error opening database", error_message);
			emit error(error_message);
			return;
		}

		english_titles.setFileName("english-titles.txt");
		if (!english_titles.open(QFile::WriteOnly))
		{
			QString error_message = "Failed to create the output file for english book titles";
	    //QMessageBox::critical(0, "Error creating english output titles file", error_message);
			emit error(error_message);
			return;
		}
		russian_titles.setFileName("russian-titles.txt");
		if (!russian_titles.open(QFile::WriteOnly))
		{
			QString error_message = "Failed to create the output file for russian book titles";
	    //QMessageBox::critical(0, "Error creating english output titles file", error_message);
			emit error(error_message);
			return;
		}

		titles_by_id.setFileName("titles-by-id.txt");
		if (!titles_by_id.open(QFile::WriteOnly))
		{
			QString error_message = "Failed to create the output file for titles-by-id";
	    //QMessageBox::critical(0, "Error creating titles-by-id output file", error_message);
			emit error(error_message);
			return;
		}
		titles_by_size.setFileName("titles-by-size.txt");
		if (!titles_by_size.open(QFile::WriteOnly))
		{
			QString error_message = "Failed to create the output file for titles-by-size";
	    //QMessageBox::critical(0, "Error creating titles-by-size output file", error_message);
			emit error(error_message);
			return;
		}

		int line = 0;
		int records = 0;
		QElapsedTimer timer, total_timer;
		timer.start();
		total_timer.start();
		QRegularExpression rx_value_insert_start("INSERT INTO `updated`");
		QRegularExpression rx_value_insert_end(".+\\)\\s*VALUES\\s*\\(");
		database_statistics.total_byte_size = 0;
		const QString data = f.readAll();
		emit message(QString("Reading the database took %1 milliseconds.").arg(timer.elapsed()));
		timer.restart();

		int index = 0;
		QRegularExpressionMatch match;
		while (1)
		{
			match = rx_value_insert_start.match(data, index);
			if (!match.hasMatch())
				break;
			index = match.capturedEnd();
			match = rx_value_insert_end.match(data, index);
			if (!match.hasMatch())
				break;
			index = match.capturedEnd() - /* get back to the opening parenthesis */ 1;

			while (index < data.length())
			{
				if (data.at(index) == '(')
				{
					int t = scan_database_record(data, index);
					if (t == -1)
						break;
					records ++;
					index += t;
				}
				else
					index ++;
				if (!(records % 100000))
				{
					emit message(QString("Records processed: %1; time elapsed (ms): %2").arg(records).arg(timer.elapsed()));
					timer.restart();
				}
			}
		}

#if 0
		for (const auto & lineData : lines)
		{
			l = lineData;
			line ++;
			if (!l.length())
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
			    //QMessageBox::critical(0, "Error parsing database record", "Failed to parse database record");
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
				emit message(QString("%1 lines read, records found: %2; time elapsed (ms): %3").arg(line).arg(records).arg(timer.elapsed()));
				qDebug() << QString("%1 lines read, records found: %2; time elapsed (ms): %3").arg(line).arg(records).arg(timer.elapsed());
				timer.restart();
			}
		}
#endif

		emit message("---------------------------------------------");
		emit message(QString("%1 lines read").arg(line));
		emit message(QString("%1 records found").arg(records));
		QStringList languages = QStringList()
				<< "bulgarian" << "russian" << "english" << /* unspecified language */"";
		for (const auto & l : languages)
		{
			emit message(QString("%1 books found: %2; total size: %3 terabytes")
				     .arg(l.isEmpty() ? "unspecified language" : l)
				     .arg(database_statistics.language_counts.operator[](l))
					.arg(((double) database_statistics.language_total_size.operator[](l)) / 1.e12));
		}

		english_titles.close();
		russian_titles.close();
		titles_by_id.close();
		titles_by_size.close();

		qDebug() << "total library size:" << (((double) database_statistics.total_byte_size) / 1.e12) << "terabytes";
		emit message(QString("Total database processing time: %1 milliseconds.").arg(total_timer.elapsed()));
		emit done();
	}

#if 0
	void scan_multithreaded(void)
	{
		QFile f;
		f.setFileName(database_filename);
		if (!f.open(QFile::ReadOnly))
		{
			QString error_message = "Can not open database file\n" + f.fileName();
			emit error(error_message);
			return;
		}

		english_titles.setFileName("english-titles.txt");
		if (!english_titles.open(QFile::WriteOnly))
		{
			QString error_message = "Failed to create the output file for english book titles";
			emit error(error_message);
			return;
		}
		russian_titles.setFileName("russian-titles.txt");
		if (!russian_titles.open(QFile::WriteOnly))
		{
			QString error_message = "Failed to create the output file for russian book titles";
			emit error(error_message);
			return;
		}

		titles_by_id.setFileName("titles-by-id.txt");
		if (!titles_by_id.open(QFile::WriteOnly))
		{
			QString error_message = "Failed to create the output file for titles-by-id";
			emit error(error_message);
			return;
		}
		titles_by_size.setFileName("titles-by-size.txt");
		if (!titles_by_size.open(QFile::WriteOnly))
		{
			QString error_message = "Failed to create the output file for titles-by-size";
			emit error(error_message);
			return;
		}

		QElapsedTimer timer, total_timer;
		total_timer.start();
		timer.start();
		database_statistics.total_byte_size = 0;
		QList<QByteArray> lines;
		{
			QByteArray data = f.readAll();
			emit message(QString("Reading the database took %1 milliseconds.").arg(timer.elapsed()));
			/* TODO: this may be wrong for utf8 encoding. */
			timer.restart();
			lines = data.split('\n');
		}
		emit message(QString("Splitting the database contents into lines took %1 milliseconds.").arg(timer.elapsed()));
		timer.restart();

		DatabaseScannerWorker * scanners[NR_DATABASE_SCANNER_THREADS];
		for (int i = 0; i < NR_DATABASE_SCANNER_THREADS; i ++)
			(scanners[i] = new DatabaseScannerWorker(lines, i, NR_DATABASE_SCANNER_THREADS))->start();

		emit message(QString("Deploying %1 database scanner threads. Wait...").arg(NR_DATABASE_SCANNER_THREADS));
		for (const auto & scanner : scanners)
			scanner->wait();

		emit message(QString("Database scanning complete. Scanning the database took %1 milliseconds.").arg(timer.elapsed()));
		timer.restart();
		emit message("Merging data from the database scanning threads...");
		unsigned t = 0;
		for (const auto & scanner : scanners)
			t += scanner->titles.length();
		database_statistics.titles.resize(t);
		unsigned index = 0;
		for (const auto & scanner : scanners)
		{
			for (int i = 0; i < scanner->titles.length(); i ++)
			{
				const QSharedPointer<QStringList> scanned_database_items = scanner->titles.at(i);
#if 1
				QString l((* scanned_database_items).at(DATABASE_RECORD_INDEX::LANGUAGE).toLower());
				bool flag;
				quint64 size = (* scanned_database_items).at(DATABASE_RECORD_INDEX::FILE_SIZE).toUInt(& flag);
				if (!flag)
				{
					emit error(QString("Could not parse database entry file size string [%1] as a number.")
						   .arg((* scanned_database_items).at(DATABASE_RECORD_INDEX::FILE_SIZE)));
					return;
				}

				database_statistics.total_byte_size += size;
				database_statistics.language_counts.operator[](l) ++;
				database_statistics.language_total_size.operator[](l) += size;

				database_statistics.titles_by_topic.operator[]((* scanned_database_items).at(DATABASE_RECORD_INDEX::TOPIC))
						<< (QStringList() << (* scanned_database_items).at(DATABASE_RECORD_INDEX::TITLE) << (* scanned_database_items).at(DATABASE_RECORD_INDEX::MD5_HASH));
#endif
				database_statistics.titles.operator[](index ++) = scanned_database_items;
			}
			delete scanner;
		}

#if 0
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

	       QString id;
	       titles_by_id.write(QString("%1\t%2\t%3\t%4\n")
				  .arg(scanned_database_items.at(DATABASE_RECORD_INDEX::TITLE))
				  .arg((id = scanned_database_items.at(DATABASE_RECORD_INDEX::IDENTIFIER_WITHOUT_DASHES)).isEmpty() ? "no-identifier" : id)
				  .arg(scanned_database_items.at(DATABASE_RECORD_INDEX::LANGUAGE))
				  .arg(scanned_database_items.at(DATABASE_RECORD_INDEX::MD5_HASH)
								 ).toUtf8()
				  );
	       titles_by_size.write(QString("%1\t%2\t%3\t%4\n")
				  .arg(scanned_database_items.at(DATABASE_RECORD_INDEX::FILE_SIZE))
				  .arg(scanned_database_items.at(DATABASE_RECORD_INDEX::FILE_NAME_EXTENSION))
				  .arg(scanned_database_items.at(DATABASE_RECORD_INDEX::MD5_HASH))
				  .arg(scanned_database_items.at(DATABASE_RECORD_INDEX::TITLE)).toUtf8());
#endif
		emit message(QString("Merging data from the database scanning threads took %1 milliseconds.").arg(timer.elapsed()));

		emit message(QString("Total number of titles: %1. Total library size: %2 terabytes")
			     .arg(database_statistics.titles.count())
			     .arg(((double) database_statistics.total_byte_size) / 1.e12));

		emit message(QString("Total database processing time: %1 milliseconds.").arg(total_timer.elapsed()));
		emit done();
	}
#endif
};
#endif

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	QThread database_scanner_thread;
	DatabaseScanner * database_scanner;
	Ui::MainWindow *ui;
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

	//void scrollToTop

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
		ui->plainTextEditTopics->moveCursor(QTextCursor::Start);
	}
private slots:
	void displayErrorMessage(const QString & error_message)
	{
		ui->plainTextEditTitles->appendPlainText("Database scan error: " + error_message);
	}
	void displayMessage(const QString & message)
	{
		ui->plainTextEditTitles->appendPlainText("Database scanner message: " + message);
	}
	void database_scanner_thread_done(void)
	{
		setEnabled(true);
		/* Clean up topics with no titles. */
		QStringList topics = ui->plainTextEditTopics->toPlainText().split('\n');
		QString filtered_topics;
		QRegularExpression rx("^(\\d+)");
		unsigned total_titles = 0;
		for (const auto & topic : topics)
		{
			QRegularExpressionMatch match = rx.match(topic);
			if (!match.hasMatch())
				continue;
			const auto titles = database_scanner->database_statistics.titles_by_topic.find(match.captured(1));
			if (titles == database_scanner->database_statistics.titles_by_topic.end())
				continue;
			filtered_topics += QString("%1 - %2 titles\n").arg(topic).arg(titles->count());
			total_titles += titles->count();
		}
		ui->plainTextEditTopics->setPlainText(filtered_topics);
		qDebug() << "Total titles with set topic:" << total_titles;
		qDebug() << "Dump of titles by topic count";
		auto i = database_scanner->database_statistics.titles_by_topic.constBegin();
		while (i != database_scanner->database_statistics.titles_by_topic.constEnd())
		{
			qDebug() << i.value().count() << "Topic:" << i.key() << "Titles:" << i.value().count();
			++ i;
		}
	}
};
