// Rui zhou at UPEI, 2010 Summer 
//ruzhou@upei.ca

import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class drawfm
{

    static File f, ff;
    static ArrayList<String> lines;
    static ArrayList<Integer> added;
    static ArrayList<State> states;
    static int comb = 2, start, max_b_plus_one = 0, r = 200, panelWidth, panelHeight, trace = 0;
    static FmPanel fm;
    static boolean umed = false, once = false;
    static String fn = "", stn, lvn;

    public static void main(String[] args) throws IOException
    {
        //System.out.println(args[0]);

        //read in a fm like file
        fn = args[0];
        if (fn.indexOf("_") >= 0)
        {
            fn = fn.substring(0, fn.indexOf("_"));  // eception !!
        }
        stn = fn + "_Nfatodfca_Set_Info";
        lvn = fn + "_Nfatodfca_Lev_Info";
//for debug
        System.out.println(fn);
        f = new File(args[0]);
        lines = new ArrayList<String>();
        if (!f.exists() && f.length() < 0)
        {
            System.out.println("The specified file is not exist");
        } else
        {
            Scanner sc = new Scanner(f);
            while (sc.hasNextLine())
            {
                String fix = sc.nextLine();
                if (fix.length() != 0)
                {
                    lines.add(fix);
                }
            }
            //System.out.println(lines.size());

        }

        //get the states
        states = new ArrayList<State>();
        added = new ArrayList<Integer>();

        for (int a = 0; a < lines.size(); a++)
        {
            Scanner lsc = new Scanner(lines.get(a).toString());
            lsc.useDelimiter(" ");
            while (lsc.hasNext())
            {
                String s = lsc.next();
                //System.out.println(s);			
                if (isNum(s))
                {
                    if (!added.contains(Integer.parseInt(s)))
                    {
                        added.add(Integer.parseInt(s));
                        //State tmp =;

                        //for (int b=0;b<states.size();b++)
                        //System.out.println("array["+b+"]: "+(states.get(b)).toString());

                        //System.out.println("after a new one add-------------------:");

                        states.add(new State(Integer.parseInt(s)));
                        //for (int b=0;b<states.size();b++)
                        //System.out.println("array["+b+"]: "+ (states.get(b)).toString());
                        //System.out.println("add state "+s);
                    }
                } else if (s.compareTo("(START)") == 0)
                {
                    lsc.next();
                    start = Integer.parseInt(lsc.next());/*
                     * System.out.println("start:"+start);
                     */
                }//could less 1?
                else if (s.charAt(0) == 'l')
                {
                    break;
                }//could less 1?

            }
        }


        //add insts set start final
        for (int a = 0; a < lines.size(); a++)
        {

            Scanner lsc = new Scanner(lines.get(a).toString());

            lsc.useDelimiter(" ");
            String head = lsc.next();
            //System.out.println(head);
            if (isNum(head) && !(lines.get(a).toString().indexOf("(FINAL)") > -1))
            {
                ((states.get(added.indexOf(Integer.parseInt(head))))).addInst(lines.get(a).toString());
                //System.out.println("add "+head+" at"+added.indexOf (Integer.parseInt(head)));
            } else if (head.compareTo("(START)") == 0)
            {
                lsc.next();
                ((states.get(added.indexOf(Integer.parseInt(lsc.next()))))).setStart();
            } else if (lines.get(a).toString().indexOf("(FINAL)") > -1)
            {
                ((states.get(added.indexOf(Integer.parseInt(head))))).setFinal();
            }
        }
        //set location



        setLocate();


// main graph
        JFrame frame = new JFrame("Fm view: " + args[0]);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        fm = new FmPanel();
        frame.getContentPane().add(fm);
        frame.pack();
        frame.setVisible(true);

//fm in text	
        JFrame sframe = new JFrame(args[0]);
        sframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JTextArea text = new JTextArea();
        for (int a = 0; a < lines.size(); a++)
        {
            text.append(lines.get(a).toString() + "\n");
        }
        Font font = new Font("Verdana", Font.BOLD, 16);
        text.setFont(font);

        JScrollPane scr = new JScrollPane(text);
        scr.setPreferredSize(new Dimension(200, 600));
        sframe.getContentPane().add(scr);
        sframe.pack();
        sframe.setVisible(true);

// set info if available
        ff = new File(stn);

        if (!ff.exists() && ff.length() < 0)
        {
            System.out.println("The level file is not exist");
        } else
        {
            JFrame mframe = new JFrame(args[0]);
            mframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);


            JTextArea mg = new JTextArea();

            Scanner scc = new Scanner(ff);
            while (scc.hasNextLine())
            {
                mg.append(scc.nextLine() + "\n");
            }
            mg.setBackground(Color.gray);
            mg.setForeground(Color.orange);
            JScrollPane mgif = new JScrollPane(mg);
            mgif.setPreferredSize(new Dimension(200, 600));

            mframe.getContentPane().add(mgif);
            mframe.pack();
            mframe.setVisible(true);
        }



    }

    public static class FmPanel extends JPanel
    {

        public FmPanel()
        {
            setBackground(Color.white);
            setPreferredSize(new Dimension(640, 480));

            FmListener listener = new FmListener();

            addMouseListener(listener);
            addMouseMotionListener(listener);

        }

        @Override
        public void paintComponent(Graphics page)
        {
            super.paintComponent(page);
            draw(page, this);
        }

        private class FmListener implements MouseListener, MouseMotionListener
        {

            boolean move = false;
            int mvit;

            public void mousePressed(MouseEvent event)
            {
                move = false;
                Point po = event.getPoint();
                for (int p = 0; p < states.size(); p++)
                {
                    if ((Math.pow((po.getX() - states.get(p).getX()), 2) + Math.pow((po.getY() - states.get(p).getY()), 2)) < 324)
                    {
                        //System.out.println("px "+po.getX()+" sx "+states.get(p).getX()+" py "+po.getY()+" sy "+states.get(p).getY());
                        move = true;
                        mvit = p;

                        //System.out.println(mvit);
                        break;
                    }
                }
            }

            public void mouseDragged(MouseEvent event)
            {
                if (move)
                {
                    Point po2 = event.getPoint();
                    states.get(mvit).setLocation((int) po2.getX(), (int) po2.getY());
                    repaint();

                }

            }

            public void mouseClicked(MouseEvent event)
            {
                Point po3 = event.getPoint();
                if ((Math.pow((po3.getX() - 11), 2) + Math.pow((po3.getY() - 11), 2)) < 89)
                {
                    comb = comb + 1;
                    if (comb == 3)
                    {
                        comb = 0;
                    }
                    repaint();
                } else if (Math.abs(po3.getX() - 12) < 8 && Math.abs(po3.getY() - 32) < 8 && max_b_plus_one > 0)
                {
                    max_b_plus_one--;
                    repaint();
                } else if (Math.abs(po3.getX() - 38) < 8 && Math.abs(po3.getY() - 32) < 8)
                {
                    max_b_plus_one++;
                    repaint();
                } // for level
                else if (Math.abs(po3.getX() - 20) < 10 && Math.abs(po3.getY() - 56) < 8)
                {
                    //System.out.println("set level");
                    ff = new File(lvn);

                    if (!ff.exists() && ff.length() < 0)
                    {
                        System.out.println("The level file is not exist");
                    } else
                    {
                        try
                        {
                            Scanner scc = new Scanner(ff);

                            int biggest_level = -1;
                            int tpint;
                            int level;
                            while (scc.hasNextLine())
                            {
                                String theline = scc.nextLine();
                                Scanner lscn = new Scanner(theline);
                                lscn.useDelimiter(" ");

                                tpint = Integer.parseInt(lscn.next());
                                level = Integer.parseInt(lscn.next());
                                if (level > biggest_level)
                                {
                                    biggest_level = level;
                                }
                                // set the level of each state

                                for (int a = 0; a < states.size(); a++)
                                {
                                    if (states.get(a).getName() == tpint)
                                    {
                                        states.get(a).setL(level);
                                    }
                                }

                            }
                            //reset the x location of each state

                            for (int a = 0; a < states.size(); a++)
                            {
                                states.get(a).setX((int) (50 + (panelWidth * 0.9) * (states.get(a).getL()) / biggest_level));

                                repaint();
                            }
                        } catch (Exception e)
                        {
                        };

                    }

                } else if (Math.abs(po3.getX() - 20) < 10 && Math.abs(po3.getY() - 96) < 8)
                {
                    for (int a = 0; a < states.size(); a++)
                    {
                        states.get(a).setY((int) (20 + (panelHeight * 0.9) * (states.get(a).getName()) / states.size()));
                    }

                    repaint();

                } else if (Math.abs(po3.getX() - 20) < 10 && Math.abs(po3.getY() - 76) < 8)
                {//trace the merge info

                    trace++;
                    if (trace == 3)
                    {
                        trace = 0;
                    }
                    if (!umed)
                    {//build array and set name
                        try
                        {
                            umed = true;// this loop works once, get the merging array
                            ArrayList<ArrayList<ArrayList<Integer>>> mapping = new ArrayList<ArrayList<ArrayList<Integer>>>();
                            ArrayList<String> explain = new ArrayList<String>();
                            File fff = new File(stn);

                            if (!fff.exists() && fff.length() < 0)
                            {
                                System.out.println("The set file is not exist");
                            } else
                            {
                                Scanner cc = new Scanner(fff);
                                while (cc.hasNextLine())
                                {
                                    String oneline = cc.nextLine();
                                    if (oneline.length() > 8 && oneline.charAt(8) == 'B')
                                    {
                                        ArrayList<ArrayList<Integer>> sets = new ArrayList<ArrayList<Integer>>();
                                        mapping.add(sets);

                                        explain.add(oneline.substring(14, oneline.length()));
                                    } else if (oneline.length() > 8 && oneline.charAt(8) == 'E')
                                    {//打酱油
                                    } else
                                    {//get the new set
                                        ArrayList<Integer> set = new ArrayList<Integer>();
                                        Scanner cs = new Scanner(oneline);
                                        cs.useDelimiter(" ");
                                        while (cs.hasNext())
                                        {
                                            set.add(Integer.parseInt(cs.next()));
                                        }
                                        mapping.get(mapping.size() - 1).add(set);

                                    }

                                }
//for debug
                                for (int a = 0; a < mapping.size(); a++)
                                {
                                    System.out.println(a + "::");
                                    for (int b = 0; b < mapping.get(a).size(); b++)
                                    {
                                        System.out.print(b + ": ");
                                        for (int c = 0; c < mapping.get(a).get(b).size(); c++)
                                        {
                                            System.out.print(mapping.get(a).get(b).get(c) + ", ");
                                        }
                                        System.out.println();
                                    }
                                }

                            }//finish build array

                            // now start set names for each state
                            for (int a = 0; a < states.size(); a++)
                            {
                                String tpname = states.get(a).getName() + "";
                                for (int b = mapping.size() - 1; b >= 0; b--)
                                {
                                    String tempname = unmerge(tpname, mapping.get(b));
                                    states.get(a).names().add("before " + explain.get(b) + ": " + tempname);
                                    tpname = tempname;
                                }

// for debug
                                for (int x = 0; x < states.get(a).names().size(); x++)
                                {
                                    System.out.println(a + " " + states.get(a).names().get(x));
                                }
                            }//names setted
                        } catch (Exception ee)
                        {
                            System.out.println(ee.getMessage());
                        }
                    }//finish build array and set name
                    repaint();
                }//end of trace button
                else if (umed == true && once == false && Math.abs(po3.getX() - 20) < 10 && Math.abs(po3.getY() - 116) < 8)
                {
                    JFrame aframe = new JFrame("Merge INfo: " + fn);
                    aframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

                    JTextArea atext = new JTextArea();

                    for (int a = 0; a < states.size(); a++)
                    {
                        String hi = states.get(a).LastName();
                        atext.append(states.get(a).getName() + ": " + hi.substring(hi.indexOf("{"), hi.length()) + "\n");
                    }


                    JScrollPane ascr = new JScrollPane(atext);
                    ascr.setPreferredSize(new Dimension(400, 400));
                    aframe.getContentPane().add(ascr);
                    aframe.pack();
                    aframe.setVisible(true);

                    once = true;


                }
            }

            public void mouseReleased(MouseEvent event)
            {
                move = false;
            }

            public void mouseEntered(MouseEvent event)
            {
            }

            public void mouseExited(MouseEvent event)
            {
            }

            public void mouseMoved(MouseEvent event)
            {
            }
            //the awesome help method

            public String unmerge(String crname, ArrayList<ArrayList<Integer>> checklist)
            {
//debug
                System.out.println("get a name" + crname);

                String toreturn = crname, toum = "", toreplace = "";
                int s = 0, l;

                //get the numbers in the string
                //first get the first digit
                while (s < toreturn.length())
                {
                    while (s < toreturn.length() && !isNum(toreturn.charAt(s) + ""))
                    {
                        s++;
                    }
                    l = 1;
                    while (s + l < toreturn.length() && isNum(toreturn.substring(s, s + l)))
                    {
                        l++;
                    }

                    // for special start
                    if (s > 0)
                    {
                        l--;
                    }

                    toum = toreturn.substring(s, s + l);
                    toreplace = "";

                    //for end
                    if (l == 0)
                    {
                        break;
                    }

//debug
                    System.out.println("from index " + s + "," + l + " get a num" + toum);
                    //try to find the num in the list ,if not found then is sink
                    // if not found the number will be replaced bu ""
                    // if found  a 0 set , then the number will be replaced by "{}"


                    for (int w = 0; w < checklist.size(); w++)
                    {
                        if (checklist.get(w).get(0) == Integer.parseInt(toum))
                        {
                            toreplace += "{";
                            for (int v = 1; v < checklist.get(w).size(); v++)
                            {
                                toreplace += checklist.get(w).get(v) + " ";
                            }

                            toreplace += "}";
                        }
                    }
                    // now replace the number
//debug
                    System.out.println("toreplace" + toreplace);
                    toreturn = toreturn.substring(0, s) + toreplace + toreturn.substring(s + l, toreturn.length());
                    s = s + toreplace.length();
                }
//debug
                System.out.println("unmergto" + toum);
                return toreturn;
            }
        }
    }

    public static void draw(Graphics page, JPanel p)
    {

        //for (int a=0;a<lines.size();a++)
        //	page.drawString(lines.get(a), p.getWidth()-100, (a+1)*16);// width? 486 adjustable?
        if (comb < 2)
        {
            page.drawString("Note: All arcs go clockwise.", p.getWidth() - 200, p.getHeight() - 5);
        }

        panelWidth = p.getWidth();
        panelHeight = p.getHeight();
        //page.setColor(Color.blue);

        //page.drawRect(1,1,479,478);

        //draw the circles
        for (int a = 0; a < states.size(); a++)
        {//System.out.println("!");
            ((states.get(a))).drawStateArc(page);
        }
        for (int a = 0; a < states.size(); a++)
        {//System.out.println("!");
            ((states.get(a))).drawState(page);
        }


        if (comb == 0)
        {
            page.setColor(Color.green);
        } else if (comb == 1)
        {
            page.setColor(Color.red);
        } else
        {
            page.setColor(Color.yellow);
        }
        page.fillOval(2, 2, 20, 20);



        page.setColor(Color.cyan);
        page.fillRect(4, 24, 16, 16);
        page.fillRect(30, 24, 16, 16);

        page.setColor(Color.black);
        page.drawString("Combine", 2, 16);
        page.drawString("" + max_b_plus_one, 20, 38);

        page.setColor(Color.cyan);
        page.drawRect(0, 48, 40, 16);
        page.drawString("LEVEL", 1, 62);

        page.drawRect(0, 68, 40, 16);
        page.drawString("TRACE", 1, 82);

        page.setColor(Color.cyan);
        page.drawRect(0, 88, 40, 16);
        page.drawString("Spread", 1, 102);

        page.setColor(Color.cyan);
        page.drawRect(0, 108, 40, 16);
        page.drawString("M-info", 1, 122);




    }

    public static boolean isNum(String s)
    {
        try
        {
            Integer.parseInt(s);
        } catch (NumberFormatException nfe)
        {
            return false;
        }
        return true;
    }

    public static void setLocate()
    {

        double angle = 2 * Math.PI / states.size(), stAngle = 3 * Math.PI / 4;
        int lv = 0;
        for (int a = 0; a < states.size(); a++)
        {//System.out.println("x "+(int)(240+Math.cos(stAngle+angle*lv)*r)+"y "+(int)(240+Math.sin(stAngle+angle*lv)*r));
            ((states.get(a))).setLocation((int) (240 + Math.cos(stAngle + angle * lv) * r), (int) (240 + Math.sin(stAngle + angle * lv) * r));
            lv++;
            //System.out.println(a+"Location: "+ ((states.get(a))).toString());
            //for (int b=0;b<states.size();b++)
            //System.out.println(b+"!!-------"+ ((states.get(b))).toString());
        }

    }

    public static class State
    {

        boolean start = false, finall = false, set;
        ArrayList<String> inst;
        int name, x, y, level;

        public State(int nam)
        {
            name = nam;//System.out.println("get"+name);
            inst = new ArrayList<String>();
        }

        public void addInst(String in)
        {
            inst.add(in);
        }

        public void setStart()
        {
            start = true;
        }

        public void setFinal()
        {
            finall = true;
        }

        public void setLocation(int locX, int locY)
        {
            x = locX;
            y = locY;
            set = true;
        }

        public boolean isStart()
        {
            return start;
        }

        public boolean set()
        {
            return set;
        }

        public int getX()
        {
            return x;
        }

        public int getY()
        {
            return y;
        }

        public int getName()
        {
            return name;
        }

        public void setX(int locX)
        {
            x = locX;
        }

        public void setY(int locY)
        {
            y = locY;
        }

        public void setL(int lev)
        {
            level = lev;
        }

        public int getL()
        {
            return level;
        }
        //for merging info
        ArrayList<String> names = new ArrayList<String>();

        ArrayList<String> names()
        {
            return names;
        }

        String LastName()
        {
            return names.get(names.size() - 1);
        }

        public void drawStateArc(Graphics page)
        {

            page.setColor(Color.green);
            for (int a = 0; a < inst.size(); a++)
            {
                drawInst(inst.get(a), page);
            }

            /*
             * page.setColor(Color.yellow);
             *
             * page.fillOval(x-18,y-18,36,36); page.setColor(Color.black);
             * page.drawString(Integer.toString(name),x-3,y+5); if
             * (start){page.setColor(Color.red);page.drawString("Start",x+3,y-10);}
             * if
             * (finall){page.setColor(Color.black);page.drawOval(x-18,y-18,36,36);}
             * System.out.println("draw"+x+" "+y);
             */
        }

        @Override
        public String toString()
        {
            return "Name : " + name + " x y: " + x + "," + y;
        }

        public void drawState(Graphics page)
        {
            page.setColor(Color.yellow);

            page.fillOval(x - 18, y - 18, 36, 36);
            page.setColor(Color.black);
            page.drawString(Integer.toString(name), x - 3, y + 5);
            if (max_b_plus_one > 0)
            {
                page.setColor(Color.red);
                page.drawString("(" + name % max_b_plus_one + "," + name / max_b_plus_one + ")", x - 12, y + 20);
            }

            if (start)
            {
                page.setColor(Color.red);
                page.drawString("Start", x + 3, y - 10);
            }
            if (finall)
            {
                page.setColor(Color.black);
                page.drawOval(x - 18, y - 18, 36, 36);
            }

            //draw trace info
            if (trace == 1)
            {
                page.setColor(Color.blue);
                //for (int a=0;a<names.size();a++)
                //page.drawString(names.get(a),x-3,y+15*(1+a) );
                String nn = names.get(names.size() - 1);
                page.drawString(nn.substring(nn.indexOf('{'), nn.length()), x - 3, y + 15);
            }
            if (trace == 2)
            {
                page.setColor(Color.blue);
                for (int a = 0; a < names.size(); a++)
                {
                    page.drawString(names.get(a), x - 3, y + 15 * (1 + a));
                }

            }
        }
    }

    public static void drawInst(String in, Graphics page)
    {
//get start , sink , and label
        Scanner insc = new Scanner(in);
        insc.useDelimiter(" ");
        int stst = Integer.parseInt(insc.next());
        String lab = insc.next();
        int sist = Integer.parseInt(insc.next());

// get location
        int sx, sy, fx, fy;
        sx = states.get(added.indexOf(stst)).getX();
        sy = states.get(added.indexOf(stst)).getY();
        fx = states.get(added.indexOf(sist)).getX();
        fy = states.get(added.indexOf(sist)).getY();
        int len = ((int) (lab.charAt(0)) - 96) % 8;// abcdefgh
//if is to self
        if (sx == fx && sy == fy)
        {

            int rad = (int) ((2.6 * Math.pow(0.5, len) + 0.707) * r / 10);
            if (comb > 0)
            {
                rad = (int) ((2.6 * Math.pow(0.5, 1) + 0.707) * r / 16);
            }
            page.drawArc(sx, sy - rad / 3, 2 * rad, 2 * rad, 160, 340);
            if (comb == 0)
            {
                page.drawString(lab, sx + 2 * rad, sy + rad);
            } else
            {
                page.drawString(lab, sx + 8 * len, sy + rad);
            }
        } else// not to self
        {
//set r according to label name 
            if (comb < 2)
            {
//System.out.println(lab.charAt(0)+"len"+len);
                int rad = (int) ((2.6 * Math.pow(0.76, len) + 0.707) * r * 1.5);//  can change this  make lines combine to one
                if (comb > 0)
                {
                    rad = (int) ((2.6 * Math.pow(0.76, 1) + 0.707) * r * 1.5);
                }
                int vecX = fx - sx;
                int vecY = fy - sy;

                double cos = Math.sqrt(vecX * vecX + vecY * vecY) / (2 * rad);//less a 2?
                double sin = Math.sqrt(1 - cos * cos);

//向顺时针旋转则: p: (x,y) --------> p': ( x*cos(-d)-y*sin(-d) , x*sin(-d)+y*cos(-d) )
                int cx = (int) (sx + (vecX * cos - vecY * sin) / cos / 2);
                int cy = (int) (sy + (vecY * cos + vecX * sin) / cos / 2);
                page.setColor(Color.green);
                int sp = 0, fp = 0;
//if(sx<cx){sp=180*Math.abs(sy-cy)/(sy-cy);}// /0?
//if(fx<cx){fp=180*Math.abs(fy-cy)/(fy-cy);}
                if (sx < cx)
                {
                    sp = 180;
                }
                if (fx < cx)
                {
                    fp = 180;
                }
                int startAngle = fp + (int) (180 / Math.PI * Math.atan(((double) (cy) - fy) / (fx - cx)));// y is opposite 
                int endAngle = (int) (180 / Math.PI * Math.atan(((double) (cy) - sy) / (sx - cx))) + sp;
//if(startAngle<0){startAngle+=360;}
//if(endAngle<0){endAngle+=360;}
                int dAngle;
                if (endAngle != startAngle)
                {
                    dAngle = endAngle - startAngle + 180 - 180 * (Math.abs(endAngle - startAngle) / (endAngle - startAngle));
                } else
                {
                    dAngle = 0;
                }
//if(dAngle>180){dAngle-=180;;}
//if (Math.abs(endAngle-startAngle)>180)
//{int tmp=endAngle;endAngle=startAngle;startAngle=tmp;}
//System.out.println("Color"+(sx%255)+","+(fx%255)+","+(cx%255) );	
                page.setColor(new Color(Math.abs(sx % 255), Math.abs(fx % 255), Math.abs(cx % 255)));
                page.drawArc(cx - rad, cy - rad, 2 * rad, 2 * rad, startAngle, dAngle);
//page.fillOval(fx-3,fy-3,6,6);
                int vecx = (sx + fx) / 2 - cx;
                int vecy = (sy + fy) / 2 - cy;
                double leng = (double) rad / (Math.sqrt((double) vecx * vecx + vecy * vecy));
                int labx = cx + (int) (leng * vecx * ((double) len / 68 + 0.98));
                int laby = cy + (int) (leng * vecy * ((double) len / 68 + 0.98));
                page.drawString(lab, labx, laby);


//page.drawRect(cx-rad,cy-rad,2*rad,2*rad);
//page.drawString("draw arc for"+in,cx-rad,cy-rad);
//page.drawString("o for"+in+"start "+startAngle+" end "+endAngle+" fy-cy "+(fy-cy)+" fx-cx "+(fx-cx),cx,cy);
            } else//draw straight lines
            {//
//tan
                int rr = 36 / 2 - 1;

                double tan = (double) (-1) * (fy - sy) / (((double) fx - sx + 0.01));
                double cos = Math.sqrt(1 / (1 + tan * tan));
                double sin = cos * tan;
//a1 b1
                int adjust = ((fx >= sx) ? 1 : -1);
                int a1 = (int) (sx - rr * sin * adjust);
                int b1 = (int) (sy - rr * cos * adjust);
//a2 b2
                int a2 = (int) (fx - rr * sin * adjust);
                int b2 = (int) (fy - rr * cos * adjust);
// set color
                page.setColor(new Color(Math.abs(sx % 255), Math.abs(fx % 220), Math.abs(((sx + fx) / 2) % 255)));
//page.setColor(new Color(255,255,255));
//main line
                page.drawLine(a1, b1, a2, b2);
//arrow
/*
                 * int lll=10; int a3=(int)(fx-(rr+lll)*sin); int
                 * b3=(int)(fy-(rr+lll)*cos);
                 *
                 * int
                 * by=Math.abs((int)Math.sqrt(lll*lll/(1+Math.pow((b2-b3)/(a2-a3)
                 * ,2))	)-b3); int ax=Math.abs((int)Math.pow((b2-b3)/(a2-a3)
                 * ,2)*(b3-by)-a3);
                 *
                 * page.drawLine(a2,b2,ax,by);
                 */
                page.fillOval(a2 - 6, b2 - 6, 12, 12);
//label

                int labx = a1 + (int) (((double) fx - sx) * (.2 + 0.066 * len));
                int laby = b1 + (int) (((double) fy - sy) * (.2 + 0.066 * len));
                page.drawString(lab, labx, laby);





            }

        }
    }
}

