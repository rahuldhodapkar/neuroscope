/***************************************************************************
                          channelPalette.h  -  description
                             -------------------
    begin                : Thur feb  26  12:06:21 EDT 2004
    copyright            : (C) 2003 by Lynn Hazan
    email                : lynn.hazan@myrealbox.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef CHANNELPALETTE_H
#define CHANNELPALETTE_H

//QT include files
#include <QVariant>
#include <qwidget.h>
#include <q3vbox.h> 
#include <q3iconview.h>
#include <QHash>
#include <qmap.h>
#include <QLabel>
#include <QCursor>
//Added by qt3to4:
#include <QDropEvent>
#include <QResizeEvent>
#include <QList>
#include <QPixmap>
#include <QMouseEvent>
#include <QDragEnterEvent>

// application specific includes
#include "channelgroupview.h"
#include "channeliconview.h"


// forward declaration
class Q3IconView;
class Q3IconViewItem;
class ChannelColors;
class SpaceWidget;

/**
  * This class represents the channel palettes of the application (anatomical and spike).
  * It receives the user selections and triggers the actions which have to be done.
  *@author Lynn Hazan
  */


class ChannelPalette : public Q3ScrollView
{
    Q_OBJECT
    
public:

    enum PaletteType {DISPLAY=0,SPIKE=1};
    
    /**Constructor.
    * @param type type of palette (anatomical or spike).
    * @param backgroundColor background color.
    * @param edition true if the item of the palette are movable, falsse otherwise.
    * @param parent parent widget.
    * @param name internal name of the palette.
    * @param fl widget flags.
    */
    ChannelPalette(PaletteType type, const QColor &backgroundColor, bool edition, QWidget* parent = 0, const char* name = 0);
    /*
   *  Destroys the object and frees any allocated resources.
   */
    ~ChannelPalette();

    /**Dispatchs the channels in several iconviews to represent the different groups of channels.
    * @param channelColors list of colors for the channels.
    * @param groupsChannels map given the list of channels for each group.
    * @param channelsGroups map given to which group each channel belongs.
    */
    void createChannelLists(ChannelColors* channelColors,QMap<int, QList<int> >* groupsChannels,QMap<int,int>* channelsGroups);

    /**Selects the channels contain in @p selectedChannels.
    * @param selectedChannels list of channels to select.
    */
    void selectChannels(const QList<int>& selectedChannels);

    /**Resets the internal information of the palette.*/
    void reset();
    
    /**Returns the list of selected channels*/
    const QList<int> selectedChannels();

    /**updates the background color of the palette.*/
    void changeBackgroundColor(QColor color);

    /**
    * Gets the channels with the @p showStatus show/hide status.
    * @return list of channels having a show/hide status equals to showStatus.
    */
    const QList<int> getShowHideChannels(bool showStatus);

    /**
    * Gets the skip status for each channel.
    * @return map between the channel and skip status.
    */
    inline const QMap<int,bool>getSkipStatus(){return channelsSkipStatus;}

    /**Interal class to represent an item in the palette. Contains a overloaded compare function to have
* the items order by alphabetic order.
*/    
    class ChannelIconItem : public Q3IconViewItem{

    public:
        ChannelIconItem(Q3IconView* parent,const QString& text,const QPixmap& icon):
            Q3IconViewItem(parent,text,icon){}

        ChannelIconItem(Q3IconView* parent,Q3IconViewItem* after,const QString& text,const QPixmap& icon):
            Q3IconViewItem(parent,after,text,icon){}

        virtual inline int compare(Q3IconViewItem* item) const{
            if(key().toInt() < item->key().toInt())
                return -1;
            else if(key().toInt() == item->key().toInt())
                return 0;
            else
                return 1;
        }
    };

    
public Q_SLOTS:
    void changeColor(QListWidgetItem *item, bool single = true);
    /**Creates a new group and fill it with the selected channels.
    */
    void createGroup();
    void setGreyScale(bool grey);
    /**Deletes the empty groups*/
    void deleteEmptyGroups();
    void selectAllChannels();
    void deselectAllChannels();
    /**Channels moved to an existing group in a specific location.*/
    void slotChannelsMoved(QString targetGroup,Q3IconViewItem* after);
    /**Channels moved around in a group.*/
    void slotChannelsMoved(const QList<int>& channelIds,QString sourceGroup,Q3IconViewItem* after);
    void trashChannelsMovedAround(const QList<int>& channelIds,QString afterId,bool beforeFirst);
    void discardChannels();
    void discardChannels(const QList<int>& channelsToDiscard);
    void discardChannels(const QList<int>& channelsToDiscard,QString afterId,bool beforeFirst);
    void discardSpikeChannels();
    void showChannels();
    void hideChannels();
    void hideUnselectAllChannels();
    void updateShowHideStatus(const QList<int>&channelIds,bool showStatus);
    void updateSkipStatus(const QMap<int,bool>& skipStatus);
    void updateSkipStatus(const QList<int>&channelIds,bool skipStatus);
    void updateColor(const QList<int>& channelIds);
    void updateColor(int channelId);
    /**Sets the channel color to the group color for all the channels in the same group has channelId.
    * The group to used is determine with the palette type.
    * @param channelId id of the reference channel.
    */
    void updateGroupColor(int channelId);
    void applyGroupColor(PaletteType paletteType);
    void applyCustomColor();
    void setEditMode(bool edition);
    void groupToMove(int sourceId,int targetId,int start, int destination);
    void removeChannelsFromTrash(const QList<int>& channelIds);
    void slotMousePressWoModificators(QString sourceGroup);
    void selectionTool(){
        emit channelsSelected(selectedChannels());
    }
    
protected Q_SLOTS:
    virtual void slotRightPressed(Q3IconViewItem* item);
    void slotMousePressMiddleButton(QListWidgetItem*item);
    void slotMousePressed(QString sourceGroupName);
    virtual void slotMidButtonPressed(const QString &sourceGroupId);
    virtual void slotClickRedraw();
    virtual void languageChange();
    virtual void createGroup(int id);
    virtual void setChannelLists();
    virtual void resizeEvent(QResizeEvent* event);
    void paintEvent (QPaintEvent*);
    void slotDragLabeltMoved(QPoint position){ensureVisible(position.x(),position.y());}
    
Q_SIGNALS:
    void singleChangeColor(int selectedChannel);
    void groupChangeColor(int groupId);
    //void channelsChangeColor(QValueList<int> selectedChannels);
    void updateShownChannels(const QList<int>& shownChannels);
    void updateHideChannels(const QList<int>& hiddenChannels);
    void paletteResized(int parentWidth,int labelSize);
    void channelsDiscarded(const QList<int>& discarded);
    void setDragAndDrop(bool dragAndDrop);
    void groupModified();
    void channelsMovedToTrash(const QList<int>&channelIds,QString afterId,bool beforeFirst);
    void channelsMovedAroundInTrash(const QList<int>& channelsToDiscard,QString afterId,bool beforeFirst);
    void channelsRemovedFromTrash(const QList<int>& channelIds);
    void channelsSelected(const QList<int>& selectedChannels);
    
private:    
    /**Pointer on the ChannelColors storing the color information for the channels.*/
    ChannelColors* channelColors;

    /**Background color.*/
    QColor backgroundColor;

    /**Prevent from emitting signal while globaly selecting items*/
    bool isInSelectItems;

    Q3VBox* verticalContainer;

    /**Dictionnary of the iconviews representing the group of channels.*/
    QHash<QString, ChannelIconView*> iconviewDict;

    /**Dictionnary of layout containing the iconviews.*/
    QHash<QString, ChannelGroupView*> channelGroupViewDict;

    /**Dummy widget used to keep the iconviews nicely display in the pannel.*/
    SpaceWidget* spaceWidget;

    /**Stores to which group each channel belongs. Pointer to the variable belonging to
    NeuroscopeDoc.*/
    QMap<int,int>* channelsGroups;

    /**Map the correspondence between the channel group ids and the channel ids.
    *Pointer to the variable belonging to NeuroscopeDoc.
    */
    QMap<int, QList<int> >* groupsChannels;

    int labelSize;
    
    /**True if the the colors are in grey-scale*/
    bool greyScale;

    /**True if a group has to be removed because all its channels have been removed.*/
    bool isGroupToRemove;

    /**Type of the palette usage: display or spike.*/
    PaletteType type;

    /**Stores show/hide status of each channel.*/
    QMap<int,bool> channelsShowHideStatus;
    
    /**True if the palette is in edit mode, false otherwise.*/
    bool edit;

    /**Stores the group currently beeing selected.*/
    QString selected;
    
    /**Stores skip status of each channel.*/
    QMap<int,bool> channelsSkipStatus;

    /**Stores the selection status of each group. The selection status is true if all the group items have been selected by a click on the group label, false otherwise.*/
    QMap<QString,bool> selectionStatus;
    
    //Functions
    
    /**
    * Updates the show/hide status of the currently slected channels.
    * @param showStatus true if the show/hide status has to be set to show, false if it has to be set to hide.
    */
    void updateShowHideStatus(bool showStatus);

    /**Draws the channel pixmap with the color specified or in grey-scale if greyScale is true.
    * The shape depends upon the edit state, circle if the palette is editable and rectangle otherwise.
    * The cicle is hollowed if the channel is shown.
    * @param painter painer use to draw the pixmap.
    * @param pixmap pixmap to paint.
    * @param color color use to paint the pixmap.
    * @param show boolean use to know the type of circle to draw.
    * @param skip boolean use to if the pixmap has to be drawn with the background color.
    */
    void drawItem(QPainter& painter, QPixmap* pixmap,QColor color, bool show, bool skip);

    /**Ensures that the trash group is always at the bottom.*/
    void moveTrashesToBottom();

    /**Moves channels around in a group.*/
    void moveChannels(const QList<int>& channelIds,QString sourceGroup,Q3IconViewItem* after);

    /**Channels moved to an empty group.*/
    void moveChannels(const QList<int>& channelIds,QString sourceGroup,QString targetGroup);

    /**Moves channels to either the trash group or the unspecified group in the spike palette.
    * @param destinationGroup the id of the group of destination.
    */
    void trashChannels(int destinationGroup);

    /**Moves the selected channels to the group @p targetGroup.
    * @param targetGroup id of the target group;
    */
    void moveChannels(int targetGroup);

    /**Creates an empty group.
    * @return the id of the new group.
    */
    int createEmptyGroup();
};

/**IUtility class used to create the channel palettes of the application (anatomical and spike)..
*/  
class SpaceWidget : public QWidget{
    Q_OBJECT
public:
    inline SpaceWidget(QWidget* parent,bool drag):QWidget(parent),drag(drag){
        setAcceptDrops(TRUE);
    }

    inline virtual void dropEvent(QDropEvent* event){
        if(event->source() == 0 || !drag){
            event->ignore();
            return;
        }


        if(event->mimeData()->hasText()){
            QString information = event->mimeData()->text();
            int groupSource = information.section("-",0,0).toInt();
            int start = information.section("-",1,1).toInt();
            //to inform that the target is the SpaceWidget, put -2 as the target group.
            emit dropLabel(groupSource,-2,start,QWidget::mapToGlobal(event->pos()).y());
        }
    }

    inline virtual void dragEnterEvent(QDragEnterEvent* event){
        if(event->source() == 0 || !drag){
            event->ignore();
            return;
        }
        if (event->mimeData()->hasText())
            event->acceptProposedAction();
    }

public Q_SLOTS:
    void setDragAndDrop(bool dragDrop){drag = dragDrop;}

Q_SIGNALS:
    void dropLabel(int sourceId,int targetId,int start, int destination);

private:
    /**True the drag and drop is allow, false otherwise.*/
    bool drag;

};

/**
  *Utility class used to create the group labels on the left side of the group boxes in the anatomical and spike palettes.
  *@author Lynn Hazan
  */
class GroupLabel : public QLabel{
    Q_OBJECT
public:
    inline GroupLabel(const QString& text,QWidget* parent):
        QLabel(text,parent){
        setAutoFillBackground(true);
    }

Q_SIGNALS:
    void middleClickOnLabel(QString sourceId);
    void leftClickOnLabel(QString sourceId);

protected:
    virtual void mousePressEvent(QMouseEvent* e){
        if(e->button() == Qt::LeftButton){

            QPoint firstClick = QWidget::mapToGlobal(e->pos());
            QString information = parent()->objectName();
            information.append(QString("-%1").arg(firstClick.y()));

            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;

            mimeData->setText(information);
            drag->setMimeData(mimeData);
            Qt::DropAction dropAction = drag->exec();
            e->accept();

            emit leftClickOnLabel(parent()->objectName());
        }
        if(e->button() == Qt::MidButton){
            emit middleClickOnLabel(parent()->objectName());
        }
    }
};

#endif // CHANNELPALETTE_H
