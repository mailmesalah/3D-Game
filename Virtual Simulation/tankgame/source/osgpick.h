// class to handle events with a pick

extern int g_speed;
extern bool g_bmute;

class PickHandler : public osgGA::GUIEventHandler {
public:

    PickHandler(osg::ref_ptr<osgText::Text> updateText):
        _updateText(updateText) {}

    ~PickHandler() {}

    bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);

    virtual void pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea);

    void setLabel(const std::string& name)
    {
        if (_updateText.get()) _updateText->setText(name);
    }

protected:

    osg::ref_ptr<osgText::Text>  _updateText;
};
