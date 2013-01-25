import java.util.*;

class HuffmanCoding {
	private int parent;
	private int lchild;
	private int rchild;
	private int weight;
	
	void setparent(int value) {
		this.parent = value;
	}
	void setlchild(int value) {
		this.lchild = value;
	}
	void setrchild(int value) {
		this.rchild = value;
	}
	void setweight(int value) {
		this.weight = value;
	}
	
	int getparent() {
		return this.parent;
	}
	int getlchild() {
		return this.lchild;
	}
	int getrchild( ) {
		return this.rchild;
	}
	int getweight() {
		return this.weight;
	}
}


public class H {
    private static ArrayList<Integer> w = new ArrayList<Integer>(); 
    private static ArrayList<HuffmanCoding> ht = new ArrayList<HuffmanCoding>();
    private static int m;
     
    private static void Init() {
       	w.add(5);
    	w.add(29);
    	w.add(7);
    	w.add(8);
    	w.add(14);
    	w.add(23);
    	w.add(3);
    	w.add(11);
        m = w.size() * 2 - 1;
        
    	for (int i = 0; i < m; ++i) {
		    ht.add(new HuffmanCoding());
		   	if (i < w.size()) ht.get(i).setweight(w.get(i));
		   	else ht.get(i).setweight(0);
		   	ht.get(i).setlchild(0);
	    	ht.get(i).setrchild(0);
	    	ht.get(i).setparent(0);
	    }
	}
    
	private static void  Select(int j, int[] s){
		int a = 999, b = 999;
		for (int i = 0; i < j; ++i){
			if (w.get(i) < a && ht.get(i).getparent() == 0) {
				a = w.get(i);
				s[0] = i;
			}
		}
		for (int i = 0; i < j; ++i){
			if (i != s[0] && w.get(i) < b && ht.get(i).getparent() == 0)  {
				b = w.get(i);
				s[1] = i;
			}
		}
	}
	
	private static void Huffman() {
		int[] s = new int[2];
		
		for (int i = w.size(); i < m; ++i){
			Select(i, s);
			
			ht.get(s[0]).setparent(i);
			ht.get(s[1]).setparent(i);
			ht.get(i).setlchild(s[0]);
			ht.get(i).setrchild(s[1]);
			ht.get(i).setweight(w.get(s[0]) + w.get(s[1]));
			w.add(w.get(s[0]) + w.get(s[1]));
		}
	}
	
	private static void Traverse() {
		for (int i = 0; i < m; ++i)
			System.out.println(i + 1 + " " + ht.get(i).getweight() + " " 
		+ ht.get(i).getparent() + " " + ht.get(i).getlchild() + " " + ht.get(i).getrchild());	
	}	
	
	private static void Coding() {
		
		
	}
	
	public static void main(String[] args) {
		Init();
		Huffman();
		Traverse();	
		Coding();
	}
}
