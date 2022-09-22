#include "mainwindow.hxx"
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	{
		QSettings s("qlg.rc", QSettings::IniFormat);
		restoreGeometry(s.value("window-geometry").toByteArray());
		restoreState(s.value("window-state").toByteArray());
		restoreState(s.value("window-state").toByteArray());
		ui->splitterMainVertical->restoreState(s.value("main-splitter-state").toByteArray());
	}
	ui->plainTextEditTitles->setUndoRedoEnabled(false);
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
		"[^\\(]*\\("	/* opening parenthesis */
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
	match = rx.match(s);
	qDebug() << "match" << (match.hasMatch() ? "":"not") << "found";

	//QString database_file = "D:/src/libgen_compact.sql";
	QString database_file = "c:/tmp/libgen_compact.sql";

	populate_topic_list();
	database_scanner = new DatabaseScanner(database_file);
	database_scanner->moveToThread(&database_scanner_thread);
	connect(&database_scanner_thread, &QThread::finished, database_scanner, &QObject::deleteLater);
	connect(&database_scanner_thread, &QThread::started, database_scanner, &DatabaseScanner::scan);
	connect(database_scanner, &DatabaseScanner::error, this, &MainWindow::displayErrorMessage);
	connect(database_scanner, &DatabaseScanner::message, this, &MainWindow::displayMessage);
	connect(database_scanner, &DatabaseScanner::done, this, &MainWindow::database_scanner_thread_done);
	setEnabled(false);
	database_scanner_thread.start();

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
		for (const auto & topic : database_scanner->database_statistics.titles_by_topic)
			for (const auto & item : topic)
				s += (item.at(0)), s += '\n';
		ui->plainTextEditTitles->setPlainText(s);
	});
	connect(ui->plainTextEditTopics, & QPlainTextEdit::cursorPositionChanged, [=] (void) -> void
	{
		QTextCursor c(ui->plainTextEditTopics->textCursor());
		c.select(QTextCursor::LineUnderCursor);
		ui->plainTextEditTopics->setTextCursor(c);
	});
	connect(ui->pushButtonListTitlesForTopic, &QPushButton::clicked, [=](void)->void
	{
		QString s;
		int i = 0;
		ui->plainTextEditTitles->clear();
		for (const auto & item : database_scanner->database_statistics.titles_by_topic.operator[](QString("%1").arg(get_selected_topic())))
			s += (item.at(0)), s += '\n', i ++;
		ui->plainTextEditTitles->setPlainText(s);
		ui->statusbar->showMessage(QString("%1 items found").arg(i));
	});
	connect(ui->pushButtonListTitlesWithNoTopic, &QPushButton::clicked, [=](void)->void
	{
		QString s;
		int i = 0;
		ui->plainTextEditTitles->clear();
		for (const auto & item : database_scanner->database_statistics.xtitles)
			if (item->topic->isEmpty())
				s += * item->title, s += '\n', i ++;
		ui->plainTextEditTitles->setPlainText(s);
		ui->statusbar->showMessage(QString("%1 items found").arg(i));
	});

	connect(ui->pushButtonDumpMd5Hashes, &QPushButton::clicked, [=](void)->void
	{
		QFile f("libgen-md5-hashes.txt");
		if (!f.open(QFile::WriteOnly))
		{
			QMessageBox::critical(0, "Error opening md5 hashes output file", "Failed to open md5 hashes output file for writing");
			return;
		}
		for (const auto & item : database_scanner->database_statistics.xtitles)
			f.write(((* item->md5_hash) + '\n').toLocal8Bit());
	});

	connect(ui->pushButtonFilterLanguages, &QPushButton::clicked, [=](void)->void
	{
		QStringList titles;
		ui->plainTextEditTitles->clear();
		QStringList languages;
		languages << "bulgarian" << "russian" << "english" << "";
		uint64_t total_size = 0;
		for (const auto & item : database_scanner->database_statistics.xtitles)
			if (languages.contains(item->language->toLower()))
			{
				titles << * item->title + "\t\"\"\"" + * item->identifier_without_dashes;
				total_size += item->file_size;
			}
		std::sort(titles.begin(), titles.end());
		QString s;
		for (const auto & title: titles)
			s += title + '\n';
		ui->plainTextEditTitles->setPlainText(s);
		ui->statusbar->showMessage(QString("%1 items found. Total size: %2 terabytes").arg(titles.length()).arg((double) total_size / 1000000000000));
	});

	connect(ui->pushButtonScanLanguages, &QPushButton::clicked, [=](void)->void
	{
		QMap<QString /* language */, int /* count */> languages;
		for (const auto & item : database_scanner->database_statistics.xtitles)
			languages.operator[](item->language->toLower()) ++;
		ui->plainTextEditLanguages->clear();
		QMap<QString, int>::const_iterator i = languages.constBegin();
		QString s;
		while (i != languages.constEnd()) {
			s += QString("%1\t%2\n").arg(i.key()).arg(i.value());
			i ++;
		}
		ui->plainTextEditLanguages->setPlainText(s);
		ui->plainTextEditLanguages->moveCursor(QTextCursor::Start);
	});
	connect(ui->pushButtonListTitles, &QPushButton::clicked, [=](void)->void
	{
		const auto & titles = database_scanner->database_statistics.xtitles;
		std::vector<unsigned> ind(titles.length());
		unsigned i;
		for (i = 0; i < ind.size(); ind.at(i) = i, i ++);
		std::sort(ind.begin(), ind.end(), [=] (unsigned a, unsigned b) -> bool {
			return * titles.at(a)->title < * titles.at(b)->title;
		});
		QString s;
		for (const auto & i : ind)
			s += "  " + * titles.at(i)->title + '\n';
		ui->plainTextEditTitles->clear();
		ui->plainTextEditTitles->setPlainText(s);
	});
	connect(ui->lineEditSearchTitles, &QLineEdit::returnPressed, [=](void)->void
	{
		QString s, search_text = ui->lineEditSearchTitles->text();
		ui->lineEditSearchTitles->clear();
		ui->plainTextEditTitles->clear();
		if (!search_text.length())
		{
			ui->plainTextEditTitles->setPlainText("Search string empty");
			return;
		}
#if 0
		int i = 0;
		for (const auto & item : database_scanner->database_statistics.titles)
			if ((* item).at(DATABASE_RECORD_INDEX::TITLE)->())
				s += * ((* item).at(DATABASE_RECORD_INDEX::TITLE)), s += '\n', i ++;
		ui->plainTextEditTitles->setPlainText(s);
		ui->statusbar->showMessage(QString("%1 items found").arg(i));
#endif
	});

	connect(ui->plainTextEditTitles, & QPlainTextEdit::cursorPositionChanged, [=] (void) -> void
	{
		qDebug() << "set block format";
		QTextCharFormat cf;
		cf.setBackground(Qt::yellow);
		QTextCursor c(ui->plainTextEditTitles->textCursor().block());
		QTextEdit::ExtraSelection selection;
		c.clearSelection();
		c.movePosition(QTextCursor::StartOfBlock);
		c.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

		selection.cursor = c;
		selection.format = cf;
		ui->plainTextEditTitles->setExtraSelections(QList<QTextEdit::ExtraSelection>() << selection);
	});
	ui->plainTextEditTitles->installEventFilter(this);
}

MainWindow::~MainWindow()
{
	QSettings s("qlg.rc", QSettings::IniFormat);
	s.setValue("window-geometry", saveGeometry());
	s.setValue("window-state", saveState());
	s.setValue("main-splitter-state", ui->splitterMainVertical->saveState());
	/* If any database scanner thread cleanup is needed - make sure to do so here.
	 * At this time, no cleanup is needed, so the program exits immediately. */
	delete ui;
}
