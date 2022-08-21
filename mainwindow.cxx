#include "mainwindow.hxx"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	/*
//!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT //;
//!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS //;
//!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION //;
//!40101 SET NAMES utf8mb4 //;
//!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE //;
//!40103 SET TIME_ZONE='+00:00' //;
//!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 //;
//!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 //;
//!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' //;
//!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 //;
DROP TABLE IF EXISTS `updated`;
//!40101 SET @saved_cs_client	   = @@character_set_client //;
//!40101 SET character_set_client = utf8 //;
CREATE TABLE `updated` (
	`ID` int(15) unsigned NOT NULL AUTO_INCREMENT,
	`Title` varchar(2000) DEFAULT '',
	`VolumeInfo` varchar(100) DEFAULT '',
	`Series` varchar(300) DEFAULT '',
	`Periodical` varchar(200) DEFAULT '',
	`Author` varchar(1000) DEFAULT '',
	`Year` varchar(14) DEFAULT '',
	`Edition` varchar(60) DEFAULT '',
	`Publisher` varchar(400) DEFAULT '',
	`City` varchar(100) DEFAULT '',
	`Pages` varchar(100) DEFAULT '',
	`PagesInFile` int(10) unsigned NOT NULL DEFAULT 0,
	`Language` varchar(150) DEFAULT '',
	`Topic` varchar(500) DEFAULT '',
	`Library` varchar(50) DEFAULT '',
	`Issue` varchar(100) DEFAULT '',
	`Identifier` varchar(300) DEFAULT '',
	`ISSN` varchar(9) DEFAULT '',
	`ASIN` varchar(200) DEFAULT '',
	`UDC` varchar(200) DEFAULT '',
	`LBC` varchar(200) DEFAULT '',
	`DDC` varchar(45) DEFAULT '',
	`LCC` varchar(45) DEFAULT '',
	`Doi` varchar(45) DEFAULT '',
	`Googlebookid` varchar(45) DEFAULT '',
	`OpenLibraryID` varchar(200) DEFAULT '',
	`Commentary` varchar(10000) DEFAULT '',
	`DPI` int(6) unsigned DEFAULT 0,
	`Color` varchar(1) DEFAULT '',
	`Cleaned` varchar(1) DEFAULT '',
	`Orientation` varchar(1) DEFAULT '',
	`Paginated` varchar(1) DEFAULT '',
	`Scanned` varchar(1) DEFAULT '',
	`Bookmarked` varchar(1) DEFAULT '',
	`Searchable` varchar(1) DEFAULT '',
	`Filesize` bigint(20) unsigned NOT NULL DEFAULT 0,
	`Extension` varchar(50) DEFAULT '',
	`MD5` char(32) DEFAULT '',
	`Generic` char(32) DEFAULT '',
	`Visible` char(3) DEFAULT '',
	`Locator` varchar(733) DEFAULT '',
	`Local` int(10) unsigned DEFAULT 0,
	`TimeAdded` timestamp NOT NULL DEFAULT '2000-01-01 05:00:00',
	`TimeLastModified` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
	`Coverurl` varchar(200) DEFAULT '',
	`Tags` varchar(500) DEFAULT '',
	`IdentifierWODash` varchar(300) DEFAULT '',
	PRIMARY KEY (`ID`),
	UNIQUE KEY `MD5` (`MD5`),
	KEY `Generic` (`Generic`) USING BTREE,
	KEY `VisibleTimeAdded` (`Visible`,`TimeAdded`) USING BTREE,
	KEY `TimeAdded` (`TimeAdded`) USING BTREE,
	KEY `Topic` (`Topic`(3)) USING BTREE,
	KEY `VisibleID` (`Visible`,`ID`) USING BTREE,
	KEY `VisibleTimeLastModified` (`Visible`,`TimeLastModified`,`ID`) USING BTREE,
	KEY `TimeLastModifiedID` (`TimeLastModified`,`ID`) USING BTREE,
	KEY `DOI_INDEX` (`Doi`) USING BTREE,
	KEY `Identifier` (`Identifier`),
	KEY `Language` (`Language`),
	FULLTEXT KEY `Title` (`Title`),
	FULLTEXT KEY `Author` (`Author`),
	FULLTEXT KEY `Language_FTS` (`Language`),
	FULLTEXT KEY `Extension` (`Extension`),
	FULLTEXT KEY `Publisher` (`Publisher`),
	FULLTEXT KEY `Series` (`Series`),
	FULLTEXT KEY `Year` (`Year`),
	FULLTEXT KEY `Title1` (`Title`,`Author`,`Series`,`Publisher`,`Year`,`Periodical`,`VolumeInfo`),
	FULLTEXT KEY `Tags` (`Tags`),
	FULLTEXT KEY `Identifierfulltext` (`IdentifierWODash`)
) ENGINE=MyISAM AUTO_INCREMENT=3344529 DEFAULT CHARSET=utf8;
//!40101 SET character_set_client = @saved_cs_client //;

VALUES
(
1 	1,									  `ID` int(15) unsigned NOT NULL AUTO_INCREMENT,
2 	'Handbook of Clinical Drug Data',					  `Title` varchar(2000) DEFAULT '',
3 	'',									  `VolumeInfo` varchar(100) DEFAULT '',
4 	'',									  `Series` varchar(300) DEFAULT '',
5 	'',									  `Periodical` varchar(200) DEFAULT '',
6 	'Philip Anderson',							  `Author` varchar(1000) DEFAULT '',
7 	'2001',									  `Year` varchar(14) DEFAULT '',
8 	'10',									  `Edition` varchar(60) DEFAULT '',
9 	'McGraw-Hill Medical',							  `Publisher` varchar(400) DEFAULT '',
10	'',									  `City` varchar(100) DEFAULT '',
11	'1163',									  `Pages` varchar(100) DEFAULT '',
12	1163,									  `PagesInFile` int(10) unsigned NOT NULL DEFAULT 0,
13	'English',								  `Language` varchar(150) DEFAULT '',
14	'12',									  `Topic` varchar(500) DEFAULT '',
15	'Kolxo3',								  `Library` varchar(50) DEFAULT '',
16	'17',									  `Issue` varchar(100) DEFAULT '',
17	'0-07-136362-9',							  `Identifier` varchar(300) DEFAULT '',
18	'',									  `ISSN` varchar(9) DEFAULT '',
19	'',									  `ASIN` varchar(200) DEFAULT '',
20	'',									  `UDC` varchar(200) DEFAULT '',
21	'',									  `LBC` varchar(200) DEFAULT '',
22	'',									  `DDC` varchar(45) DEFAULT '',
23	'',									  `LCC` varchar(45) DEFAULT '',
24	'',									  `Doi` varchar(45) DEFAULT '',
25	'',									  `Googlebookid` varchar(45) DEFAULT '',
26	'',									  `OpenLibraryID` varchar(200) DEFAULT '',
27	'',									  `Commentary` varchar(10000) DEFAULT '',
28	0,									  `DPI` int(6) unsigned DEFAULT 0,
29	'',									  `Color` varchar(1) DEFAULT '',
30	'',									  `Cleaned` varchar(1) DEFAULT '',
31	'',									  `Orientation` varchar(1) DEFAULT '',
32	'',									  `Paginated` varchar(1) DEFAULT '',
33	'',									  `Scanned` varchar(1) DEFAULT '',
34	'',									  `Bookmarked` varchar(1) DEFAULT '',
35	'1',									  `Searchable` varchar(1) DEFAULT '',
36	3627486,								  `Filesize` bigint(20) unsigned NOT NULL DEFAULT 0,
37	'pdf',									  `Extension` varchar(50) DEFAULT '',
38	'7b2a4d53fde834e801c26a2bab7e0240',					  `MD5` char(32) DEFAULT '',
39	'',									  `Generic` char(32) DEFAULT '',
40	'',									  `Visible` char(3) DEFAULT '',
41	'B_Biology/Handbook of Clinical Drug Data (10th Edition)(1163s).pdf',	  `Locator` varchar(733) DEFAULT '',
42	0,									  `Local` int(10) unsigned DEFAULT 0,
43	'2009-07-20 03:45:11',							  `TimeAdded` timestamp NOT NULL DEFAULT '2000-01-01 05:00:00',
44	'2019-12-21 21:23:21',							  `TimeLastModified` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
45	'0/7b2a4d53fde834e801c26a2bab7e0240.jpg',				  `Coverurl` varchar(200) DEFAULT '',
46	'',									  `Tags` varchar(500) DEFAULT '',
47	'0071363629'								  `IdentifierWODash` varchar(300) DEFAULT '',
),
	 */
	QRegularExpression rx(
		"[^\\(]*\\("		/* opening parenthesis */
		"(\\d+),"	/* id */
		"'([^']*)',"	/* title */
		"'([^']*)',"	/* volume info */
		"'([^']*)',"	/* series */
		"'([^']*)',"	/* periodical */
		"'([^']*)',"	/* author */
		"'([^']*)',"	/* year */
		"'([^']*)',"	/* edition */
		"'([^']*)',"	/* publisher */
		"'([^']*)',"	/* city */
		"'([^']*)',"	/* pages */
		"(\\d+),"	/* pages in file */
		"'([^']*)',"	/* language */
		"'([^']*)',"	/* topic */
		"'([^']*)',"	/* library */
		"'([^']*)',"	/* issue */
		"'([^']*)',"	/* identifier */
		"'([^']*)',"	/* issn */
		"'([^']*)',"	/* asin */
		"'([^']*)',"	/* udc */
		"'([^']*)',"	/* lbc */
		"'([^']*)',"	/* ddc */
		"'([^']*)',"	/* lcc */
		"'([^']*)',"	/* doi */
		"'([^']*)',"	/* google book id */
		"'([^']*)',"	/* open library id */
		"'([^']*)',"	/* commentary */
		"(\\d+),"	/* dpi */
		"'([^']*)',"	/* color */
		"'([^']*)',"	/* cleaned */
		"'([^']*)',"	/* orientation */
		"'([^']*)',"	/* paginated */
		"'([^']*)',"	/* scanned */
		"'([^']*)',"	/* bookmarked */
		"'([^']*)',"	/* searchable */
		"(\\d+),"	/* file size */
		"'([^']*)',"	/* file name extension */
		"'([^']*)',"	/* md5 hash */
		"'([^']*)',"	/* generic */
		"'([^']*)',"	/* visible */
		"'([^']*)',"	/* locator */
		"(\\d+),"	/* local */
		"'([^']*)',"	/* time added */
		"'([^']*)',"	/* time last modified */
		"'([^']*)',"	/* cover url */
		"'([^']*)',"	/* tags */
		"'([^']*)'"	/* identifier without dashes */
		"\\)"		/* closing parenthesis */

	);
	QRegularExpression rx_value_insert(".+\\)\\s*VALUES\\s*\\(");
	QRegularExpressionMatch match;
	QString s =
		"(1,"
		"'Handbook of Clinical Drug Data',"
		"'',"
		"'',"
		"'',"
		"'Philip Anderson',"
		"'2001',"
		"'10',"
		"'McGraw-Hill Medical',"
		"'',"
		"'1163',"
		"1163,"
		"'English',"
		"'12',"
		"'Kolxo3',"
		"'17',"
		"'0-07-136362-9',"
		"'',"
		"'',"
		"'',"
		"'',"
		"'',"
		"'',"
		"'',"
		"'',"
		"'',"
		"'',"
		"0,"
		"'',"
		"'',"
		"'',"
		"'',"
		"'',"
		"'',"
		"'1',"
		"3627486,"
		"'pdf',"
		"'7b2a4d53fde834e801c26a2bab7e0240',"
		"'',"
		"'',"
		"'B_Biology/Handbook of Clinical Drug Data (10th Edition)(1163s).pdf',"
		"0,"
		"'2009-07-20 03:45:11',"
		"'2019-12-21 21:23:21',"
		"'0/7b2a4d53fde834e801c26a2bab7e0240.jpg',"
		"'',"
		"'0071363629'"
		")"
	;
	QString s1 = "INSERT INTO `updated` (`ID`, `Title`, `VolumeInfo`, `Series`, `Periodical`, `Author`, `Year`, `Edition`, `Publisher`, `City`, `Pages`, `PagesInFile`, `Language`, `Topic`, `Library`, `Issue`, `Identifier`, `ISSN`, `ASIN`, `UDC`, `LBC`, `DDC`, `LCC`, `Doi`, `Googlebookid`, `OpenLibraryID`, `Commentary`, `DPI`, `Color`, `Cleaned`, `Orientation`, `Paginated`, `Scanned`, `Bookmarked`, `Searchable`, `Filesize`, `Extension`, `MD5`, `Generic`, `Visible`, `Locator`, `Local`, `TimeAdded`, `TimeLastModified`, `Coverurl`, `Tags`, `IdentifierWODash`) VALUES (";
	match = rx.match(s);
	qDebug() << "match" << (match.hasMatch() ? "":"not") << "found";

	QString database_file = "D:/src/libgen_compact.sql";

	database_scanner = new DatabaseScanner(database_file);
	database_scanner->moveToThread(&database_scanner_thread);
	connect(&database_scanner_thread, &QThread::finished, database_scanner, &QObject::deleteLater);
	connect(&database_scanner_thread, &QThread::started, database_scanner, &DatabaseScanner::scan);
	connect(database_scanner, &DatabaseScanner::error, this, &MainWindow::displayErrorMessage);
	connect(database_scanner, &DatabaseScanner::message, this, &MainWindow::displayMessage);
	connect(database_scanner, &DatabaseScanner::done, this, &MainWindow::database_scanner_thread_done);
	database_scanner_thread.start();
#if 0
	QFile f;
	f.setFileName(database_file);
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
	while (1)
	{
		if (f.atEnd())
			break;
		line ++;
		if (!(l = f.readLine()).length())
			continue;
		if (!l.startsWith("INSERT INTO `updated`"))
			continue;
		match = rx_value_insert.match(l);
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
#endif

	connect(ui->pushButtonLoadEnglishTitles, &QPushButton::clicked, [=](void)->void
	{
		QFile f("english-titles.txt");
		if (!f.open(QFile::ReadOnly))
		{
			QMessageBox::critical(0, "Error opening english titles file", "Failed to open the english book titles file");
			return;
		}
		ui->plainTextEditTitles->clear();
		ui->plainTextEditTitles->setPlainText(f.readAll());
	});
	connect(ui->pushButtonPopulateTitlesByTopic, &QPushButton::clicked, [=](void)->void
	{
		QString s;
		ui->plainTextEditTitles->clear();
		for (const auto & topic : database_statistics.titles_by_topic)
			for (const auto & item : topic)
				s += (item.at(0)), s += '\n';
		ui->plainTextEditTitles->setPlainText(s);
	});
	connect(ui->plainTextEditTopics, & QPlainTextEdit::cursorPositionChanged, [=] (void) -> void
	{
		QTextCursor c(ui->plainTextEditTopics->textCursor());
		c.select(QTextCursor::LineUnderCursor);
		ui->plainTextEditTopics->setTextCursor(c);
		qDebug() << "topic selected:" << get_selected_topic();
	});
	connect(ui->pushButtonListTitlesForTopic, &QPushButton::clicked, [=](void)->void
	{
		QString s;
		int i = 0;
		ui->plainTextEditTitles->clear();
			for (const auto & item : database_statistics.titles_by_topic.operator[](QString("%1").arg(get_selected_topic())))
				s += (item.at(0)), s += '\n', i ++;
		ui->plainTextEditTitles->setPlainText(s);
		ui->statusbar->showMessage(QString("%1 items found").arg(i));
	});
	populate_topic_list();
}

MainWindow::~MainWindow()
{
	/* If any database scanner thread cleanup is needed - make sure to do so here.
	 * At this time, no cleanup is needed, so the program exits immediately. */
	delete ui;
}
