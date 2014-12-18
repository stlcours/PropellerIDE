#include "ColorScheme.h"

ColorScheme::ColorScheme()
{
    mName = "default";
    mFileName = QDir(QStandardPaths::writableLocation(
                QStandardPaths::DataLocation)).filePath(mName + ".theme.conf");

    // Default Colors
    colors[EditorFG]            = (color) { QColor(0  ,0  ,0  )   , "Editor_Background"    };
    colors[EditorBG]            = (color) { QColor(255,248,192)   , "Editor_Foreground"    };
    colors[EditorHL]            = (color) { QColor(255,255,0  )   , "Editor_Highlight"     };

    colors[ConBG]               = (color) { QColor(255,248,192)   , "CON_Background"       };
    colors[VarBG]               = (color) { QColor(255,223,191)   , "VAR_Background"       };
    colors[ObjBG]               = (color) { QColor(255,191,191)   , "OBJ_Background"       };
    colors[PubBG]               = (color) { QColor(191,223,255)   , "PUB_Background"       };
    colors[PriBG]               = (color) { QColor(191,248,255)   , "PRI_Background"       };
    colors[DatBG]               = (color) { QColor(191,255,200)   , "DAT_Background"       };

    // Syntax Highlighting
    colors[SyntaxNumbers]       = (color) { Qt::magenta           , "Syntax_Numbers"       };
    colors[SyntaxFunctions]     = (color) { Qt::blue              , "Syntax_Functions"     };
    colors[SyntaxKeywords]      = (color) { Qt::darkBlue          , "Syntax_Keywords"      };
    colors[SyntaxPreprocessor]  = (color) { Qt::darkYellow        , "Syntax_Preprocessor"  };
    colors[SyntaxQuotes]        = (color) { Qt::red               , "Syntax_Quotes"        };
    colors[SyntaxLineComments]  = (color) { Qt::darkGreen         , "Syntax_Line_Comments" };
    colors[SyntaxBlockComments] = (color) { Qt::darkGreen         , "Syntax_Block_Comments"};

    if( QFile::exists(mFileName) ){
        load();
    }
    else
    {
        save();
    }

}

void ColorScheme::save()
{
    QSettings theme_settings(mFileName, QSettings::NativeFormat);
    theme_settings.beginGroup("Colors");

    QMap<int, color>::iterator i;
    for (i = colors.begin(); i != colors.end(); ++i)
    {
        theme_settings.setValue(i.value().key,i.value().color.name());
    }

    theme_settings.endGroup();
}


void ColorScheme::load()
{
    QSettings theme_settings(mFileName, QSettings::NativeFormat);
    theme_settings.beginGroup("Colors");

    QMap<int, color>::iterator i;
    for (i = colors.begin(); i != colors.end(); ++i)
    {
        QString strNamedColor = theme_settings.value(i.value().key).toString();

        QColor qcColor = QColor(strNamedColor);
        if( qcColor.isValid() ){
            i.value().color = qcColor;
        }
    }

    theme_settings.endGroup();
}


QColor ColorScheme::getColor(ColorScheme::Color key){
    return colors[key].color;
};

const QMap<int, ColorScheme::color>& ColorScheme::getColorList() const
{
    return colors;
}
