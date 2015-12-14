/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef PLAYING_WITH_COCOS3D_CUSTOMS_MENU_H
#define PLAYING_WITH_COCOS3D_CUSTOMS_MENU_H

#include "cocos_include.h"
#include "cocos2d.h"
#include <string>

class cocos2d::Touch;

NS_BEGIN(elloop);


/** @brief A Menu for touch handling.
* 
* Features and Limitation:
*  - You can add MenuItem objects in runtime using addChild.
*  - But the only accepted children are MenuItem objects.
*/
class Menu : public cocos2d::Layer
{
public:
    /**
     * Menu state, it's used internally.
     */
    enum class State
    {
        WAITING,
        TRACKING_TOUCH,
    };
    
    /**
     *@brief Creates an empty Menu.
     */
    static Menu* create();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // VS2013 does not support nullptr in variable args lists and variadic templates are also not supported.
    typedef MenuItem* M;
    static Menu* create(M m1, std::nullptr_t listEnd) { return variadicCreate(m1, NULL); }
    static Menu* create(M m1, M m2, std::nullptr_t listEnd) { return variadicCreate(m1, m2, NULL); }
    static Menu* create(M m1, M m2, M m3, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    // On WP8 for lists longer than 10 items, use createWithArray or variadicCreate with NULL as the last argument.
    static Menu* variadicCreate(MenuItem* item, ...);
#else
    /** Creates a Menu with MenuItem objects. */
    static Menu* create(cocos2d::MenuItem* item, ...) CC_REQUIRES_NULL_TERMINATION;
#endif

    /** 
     * Creates a Menu with a Array of MenuItem objects.
     * @js NA
     */
    static Menu* createWithArray(const cocos2d::Vector<cocos2d::MenuItem*>& arrayOfItems);

    /**
     * Creates a Menu with it's item, then use addChild() to add 
     * other items. It is used for script, it can't init with undetermined
     * number of variables.
     * @js NA
     */
    static Menu* createWithItem(cocos2d::MenuItem* item);
    
    /** Creates a Menu with MenuItem objects.
     * @js NA
     */
    static Menu* createWithItems(cocos2d::MenuItem *firstItem, va_list args);

    /** Align items vertically. */
    void alignItemsVertically();

    /** Align items vertically with padding.
    @since v0.7.2
    */
    void alignItemsVerticallyWithPadding(float padding);

    /** Align items horizontally. */
    void alignItemsHorizontally();
    
    /** Align items horizontally with padding.
    @since v0.7.2
    */
    void alignItemsHorizontallyWithPadding(float padding);

    /** Align items in rows of columns. */
    void alignItemsInColumns(int columns, ...) CC_REQUIRES_NULL_TERMINATION;
    
    /** Align items in rows of columns. */
    void alignItemsInColumns(int columns, va_list args);
    
    /** Align items in array of columns.
     * @js NA
     */
    void alignItemsInColumnsWithArray(const cocos2d::ValueVector& rows);

    /** Align items in columns of rows. */
    void alignItemsInRows(int rows, ...) CC_REQUIRES_NULL_TERMINATION;
    
    /** Align items in columns of rows. */
    void alignItemsInRows(int rows, va_list args);
    
    /** Align items in array of rows.
     * @js NA
     */
    void alignItemsInRowsWithArray(const cocos2d::ValueVector& columns);

    /**
     * Determines if the menu is enable.
     * @see `setEnabled(bool)`.
     * @return whether the menu is enabled or not.
     */
    virtual bool isEnabled() const { return _enabled; }

    /**
     * Set whether the menu is visible.
     * The default value is true, a menu is default to visible.
     *@param value true if menu is enable, false if menu is disable.
     */
    virtual void setEnabled(bool value) { _enabled = value; };

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) override;
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) override;
    
    // overrides
    virtual void removeChild(cocos2d::Node* child, bool cleanup) override;
    
    virtual void addChild(cocos2d::Node * child) override;
    virtual void addChild(cocos2d::Node * child, int zOrder) override;
    virtual void addChild(cocos2d::Node * child, int zOrder, int tag) override;
    virtual void addChild(cocos2d::Node * child, int zOrder, const std::string &name) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void setOpacityModifyRGB(bool bValue) override {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) const override { return false;}

    virtual std::string getDescription() const override;

CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    Menu() : _selectedItem(nullptr), _selectedWithCamera(nullptr) {}
    virtual ~Menu();

    /** initializes an empty Menu */
    bool init() override;

    /** initializes a Menu with a NSArray of MenuItem objects */
    bool initWithArray(const cocos2d::Vector<cocos2d::MenuItem*>& arrayOfItems);

protected:

    /** whether or not the menu will receive events */
    bool _enabled;

    virtual cocos2d::MenuItem* getItemForTouch(cocos2d::Touch * touch, const cocos2d::Camera *camera);
    State _state;
    cocos2d::MenuItem *_selectedItem;
    const cocos2d::Camera *_selectedWithCamera;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Menu);
};

// end of _2d group
/// @}

NS_END(elloop);

#endif//PLAYING_WITH_COCOS3D_CUSTOMS_MENU_H
