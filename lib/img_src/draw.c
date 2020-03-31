//	gcc -o a draw.c `pkg-config --cflags --libs gtk+-2.0`
//	./a
// ` ` ./'"\|'''''¡®¡¯¡®¡¯¡¤~¡¤¡£````
//ttps://blog.csdn.net/rong_toa/article/details/78219524
#include <cairo.h>	// 绘图所需要的头文件
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>   //键盘头文件，GDK_Up在这声明   

static GtkWidget *window = NULL;
static GdkPixmap *pixmap = NULL;
int Gtklabel_w = 240;
int Gtklabel_h = 320; 

static gbooleanscribble_configure_event(GtkWidget *widget,GdkEventConfigure *event,gpointer data)
{   
	if (pixmap)   
		g_object_unref(G_OBJECT (pixmap));   
	pixmap = gdk_pixmap_new (widget->window,   widget->allocation.width,   widget->allocation.height,-1);   
	gdk_draw_rectangle (pixmap,widget->style->white_gc,TRUE,0,0,widget->allocation.width,widget->allocation.height);   
	return TRUE;
}
static gboolean scribble_expose_event(GtkWidget *widget,GdkEventExpose *event,gpointer data)
{   
	gdk_draw_drawable(widget->window,widget->style->fg_gc[GTK_WIDGET_STATE (widget)],pixmap,event->area.x, event->area.y,event->area.x, event->area.y,event->area.width,event->area.height);   
	return FALSE;
}
static void draw_brush(GtkWidget *widget, gdouble x, gdouble y)
{   GdkRectangle update_rect;
	update_rect.x = x - 3;
	update_rect.y = y - 3;
	update_rect.width = 6;
	update_rect.height = 6;
	gdk_draw_rectangle(pixmap,widget->style->black_gc,TRUE,update_rect.x, update_rect.y,update_rect.width, update_rect.height);
	gdk_window_invalidate_rect (widget->window, &update_rect,FALSE);
}
static gboolean scribble_button_press_event(GtkWidget *widget,GdkEventButton *event,gpointer data)
{   
	if (pixmap == NULL)
		return FALSE;
	if (event->button == 1)
		draw_brush(widget, event->x, event->y);
	return TRUE;
}
static gboolean scribble_motion_notify_event(GtkWidget *widget,GdkEventMotion *event,gpointer data)
{   int x, y;
	GdkModifierType state;
	if (pixmap == NULL)
		return FALSE;
	gdk_window_get_pointer(event->window, &x, &y, &state);
	if (state & GDK_BUTTON1_MASK)
		draw_brush(widget, x, y);
	return TRUE;
}

static gboolean checkerboard_expose(GtkWidget *da, GdkEventExpose *event,gpointer data)
{   gint i, j, xcount, ycount;
	GdkGC *gc1, *gc2;
	GdkColor color;
	#define CHECK_SIZE 10
	#define SPACING 2   
	gc1 = gdk_gc_new (da->window);
	color.red = 30000;
	color.green = 0;
	color.blue = 30000;
	gdk_gc_set_rgb_fg_color (gc1, &color);
	gc2 = gdk_gc_new (da->window);
	color.red = 65535;
	color.green = 65535;
	color.blue = 65535;
	gdk_gc_set_rgb_fg_color (gc2, &color);
	xcount = 0;   i = SPACING;
	while (i < da->allocation.width)
	{
		j = SPACING;
		ycount = xcount % 2;
		while (j < da->allocation.height)
		{
			GdkGC *gc;
			if (ycount % 2)	
				gc = gc1;
			else
				gc = gc2;
			gdk_draw_rectangle(da->window, gc, TRUE,i, j, CHECK_SIZE, CHECK_SIZE);
			j += CHECK_SIZE + SPACING;
			++ycount;
		}
		i += CHECK_SIZE + SPACING;
		++xcount;
	}
	g_object_unref(G_OBJECT (gc1));
	g_object_unref (G_OBJECT (gc2));
	return TRUE;
}

gboolean deal_key_press(GtkWidget *widget, GdkEventKey  *event, gpointer data)  
{            
	switch(event->keyval)
	{   // 键盘键值类型          
		case GDK_Up:	printf("Up\n");		break;          
		case GDK_Left:	printf("Left\n");	break;          
		case GDK_Right:	printf("Right\n");	break;          
		case GDK_Down:	printf("Down\n");	break;      
	}        
	int key = event->keyval; // 获取键盘键值类型      
	printf("keyval = %d\n", key);        
	return TRUE;  
}	

void deal_button_clicked(GtkWidget *widget, gpointer data)
{	
	startx += 20;	
	if(startx >= Gtklabel_w)
	{		
		startx = 0;	
	} 	
	gtk_widget_queue_draw(GTK_WIDGET(data) );	// 更新刷图区域，刷新整个窗口
} 

int main (int argc,char* argv[])
{
	GtkWidget *frame;
	GtkWidget *vbox;
	GtkWidget *da;
	GtkWidget *label;
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "绘图软件");
	g_signal_connect (G_OBJECT(window), "delete_event",G_CALLBACK (gtk_main_quit), NULL);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	vbox = gtk_vbox_new (FALSE, 8);
	gtk_container_set_border_width (GTK_CONTAINER(vbox), 8);
	gtk_container_add (GTK_CONTAINER (window), vbox);
	label = gtk_label_new(NULL);
	gtk_label_set_markup (GTK_LABEL (label),"<u>主屏区域</u>");
	gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
	frame = gtk_frame_new (NULL);   
	gtk_frame_set_shadow_type(GTK_FRAME (frame),GTK_SHADOW_IN);
	gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);
	da = gtk_drawing_area_new();
	gtk_widget_set_size_request (da, Gtklabel_w, Gtklabel_h);
	gtk_container_add (GTK_CONTAINER (frame), da);
	// "key-press-event" 与 deal_key_press 连接      
	g_signal_connect(window, "key-press-event",G_CALLBACK(deal_key_press), NULL); 

	GtkWidget *table = gtk_table_new(5, 5, TRUE);	// 表格布局容器	
	gtk_container_add(GTK_CONTAINER(window), table); // 容器加入窗口 	
	GtkWidget *button = gtk_button_new_with_label("click me");		// 按钮	
	g_signal_connect(button, "clicked", G_CALLBACK(deal_button_clicked), window);	
	gtk_table_attach_defaults(GTK_TABLE(table), button, 3, 4, 4, 5);// 把按钮加入布局 	
	// 绘图事件信号与回调函数的连接	
	//g_signal_connect(window, "expose-event", G_CALLBACK(on_expose_event), NULL); 	
	gtk_widget_set_app_paintable(window, TRUE);	// 允许窗口可以绘图 		
	//g_signal_connect (da, "expose_event",G_CALLBACK(scribble_expose_event), NULL);
	//g_signal_connect (da, "configure_event",G_CALLBACK (scribble_configure_event), NULL);
	//g_signal_connect (da, "motion_notify_event",G_CALLBACK (scribble_motion_notify_event), NULL);
	//g_signal_connect (da, "button_press_event",G_CALLBACK (scribble_button_press_event), NULL);
	//gtk_widget_set_events(da, gtk_widget_get_events (da)|GDK_LEAVE_NOTIFY_MASK|GDK_BUTTON_PRESS_MASK|GDK_POINTER_MOTION_MASK|GDK_POINTER_MOTION_HINT_MASK);
	gtk_widget_show_all(window);
	gtk_main();
	draw_brush(label,6,6);
	return FALSE;
}

#if(0)


//版权声明：本文为CSDN博主「lianghe_work」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/lianghe_work/article/details/47152271
#include <cairo.h>	// 绘图所需要的头文件
#include <gtk/gtk.h> 
int startx = 0;
int w = 400;
int h = 300; // 绘图事件
gboolean on_expose_event(GtkWidget * widget, GdkEventExpose *event, gpointer data)
{	
	cairo_t *cr = gdk_cairo_create(widget->window);	// 创建cairo环境，注意参数 	// 画背景图	// 获取图片	
	GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file("./image/back.jpg", NULL); 	// 指定图片大小	
	GdkPixbuf* dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR);		// dst_pixbuf作为cr环境的画图原材料，(0, 0)：画图的起点坐标	
	gdk_cairo_set_source_pixbuf(cr, dst_pixbuf, 0, 0);	cairo_paint(cr);	// 绘图		// 释放资源	
	g_object_unref(dst_pixbuf);	g_object_unref(src_pixbuf); 	// 画笑脸	
	src_pixbuf = gdk_pixbuf_new_from_file("./image/face.png", NULL);	
	dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, 80, 80, GDK_INTERP_BILINEAR);	
	gdk_cairo_set_source_pixbuf(cr, dst_pixbuf, startx, (h/10)*3);	
	cairo_paint(cr);	
	g_object_unref(dst_pixbuf);	
	g_object_unref(src_pixbuf); 	/*	// 绘图与写字共存的测试	// 如果绘完图片后想继续写字或画线，	// 必须手动设置画笔颜色
	cairo_set_source_rgb()	// 否则，字体或线条会被图片覆盖。	
	cairo_set_source_rgb(cr, 0.627, 0, 0);  // 设置字体颜色	
	cairo_set_font_size(cr, 40.0);			// 设置字体大小	
	cairo_move_to(cr, 50.0, 130.0);			// 写字的起点坐标	
	cairo_show_text(cr, "This is a test");	// 写字	*/ 	
	cairo_destroy(cr);	// 回收所有Cairo环境所占用的内存资源 	
	return FALSE;	// 必须返回FALSE
} 
	// 按钮按下回调函数
void deal_button_clicked(GtkWidget *widget, gpointer data)
{	
	startx += 20;	
	if(startx >= w)
	{		
		startx = 0;	
	} 	
	gtk_widget_queue_draw(GTK_WIDGET(data) );	// 更新刷图区域，刷新整个窗口
} 
int main (int argc, char *argv[])
{	
	gtk_init (&argc, &argv); 	
	GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL); // 顶层窗口	
	g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);	
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	// 中央位置显示	
	gtk_widget_set_size_request(window, 400, 300);		    // 窗口最小大小	
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);	// 固定窗口的大小 	
	GtkWidget *table = gtk_table_new(5, 5, TRUE);	// 表格布局容器	
	gtk_container_add(GTK_CONTAINER(window), table); // 容器加入窗口 	
	// button	
	GtkWidget *button = gtk_button_new_with_label("click me");		// 按钮	
	g_signal_connect(button, "clicked", G_CALLBACK(deal_button_clicked), window);	
	gtk_table_attach_defaults(GTK_TABLE(table), button, 3, 4, 4, 5);// 把按钮加入布局 	
	// 绘图事件信号与回调函数的连接	
	g_signal_connect(window, "expose-event", G_CALLBACK(on_expose_event), NULL); 	
	gtk_widget_set_app_paintable(window, TRUE);	// 允许窗口可以绘图 	
	gtk_widget_show_all(window);	// 显示所有控件 	
	gtk_main();		
	return 0;
}



//版权声明：本文为CSDN博主「lianghe_work」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/lianghe_work/article/details/47150709

#include <gtk/gtk.h>  // 头文件  
#include <gdk/gdkkeysyms.h>   //键盘头文件，GDK_Up在这声明    
// 键盘按下事件处理函数  
gboolean deal_key_press(GtkWidget *widget, GdkEventKey  *event, gpointer data)  
{            
	switch(event->keyval)
	{   // 键盘键值类型          
		case GDK_Up:	printf("Up\n");		break;          
		case GDK_Left:	printf("Left\n");	break;          
		case GDK_Right:	printf("Right\n");	break;          
		case GDK_Down:	printf("Down\n");	break;      
	}        
	int key = event->keyval; // 获取键盘键值类型      
	printf("keyval = %d\n", key);        
	return TRUE;  
}    

int main( int argc, char *argv[] )  
{      
	gtk_init(&argc, &argv);     // 初始化        
	// 创建顶层窗口      
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);      
	// 设置窗口的标题      
	gtk_window_set_title(GTK_WINDOW(window), "key_event");      
	// 设置窗口在显示器中的位置为居中      
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);      
	// 设置窗口的最小大小      
	gtk_widget_set_size_request(window, 400, 300);      
	// "destroy" 和 gtk_main_quit 连接      
	g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit), NULL);        
	// "key-press-event" 与 deal_key_press 连接      
	g_signal_connect(window, "key-press-event",G_CALLBACK(deal_key_press), NULL);        
	gtk_widget_show_all(window);    // 显示窗口全部控件        
	gtk_main();     // 主事件循环        
	return 0;
}  
#endif