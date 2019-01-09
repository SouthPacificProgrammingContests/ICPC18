/**
 * The cable graph is prime-free, and thus a permutation graph, so can be described as the intersection of two linear orders.
 * We construct two such orderings, which gives us a reachability index allowing each query to be answered in constant time.
 * Runs in O(N+Q).
 */
import java.io.*;
import java.util.*;

class Extension {
    char type; // 'L' or 'P'
    int target;
}

class Query {
    int from, to;
}

class Input {
    Extension extensions[];
    Query queries[];

    Input(int N, int Q) {
        extensions = new Extension[N];
        queries = new Query[Q];
    }

    static Input parse(BufferedReader reader) throws IOException {
        String NQ[] = reader.readLine().split(" ");
        int N = Integer.parseInt(NQ[0]);
        int Q = Integer.parseInt(NQ[1]);
        Input input = new Input(N, Q);
        for ( int e = 0; e < N; e++ ) {
            String typeTarget[] = reader.readLine().split(" ");
            input.extensions[e] = new Extension();
            input.extensions[e].type = typeTarget[0].charAt(0);
            input.extensions[e].target = Integer.parseInt(typeTarget[1]);
        }
        for ( int q = 0; q < Q; q++ ) {
            String fromTo[] = reader.readLine().split(" ");
            input.queries[q] = new Query();
            input.queries[q].from = Integer.parseInt(fromTo[0]);
            input.queries[q].to = Integer.parseInt(fromTo[1]);
        }
        return input;
    }
}

//--------------------------- PermutationBuilder --------------------

// class for efficient insertion of "next" integer before or after existing one
// essentially a double-linked list with random access by value
class PermutationBuilder {
    private static class IndexData {
        int before, after;
    }
    private ArrayList<IndexData> perm = new ArrayList<IndexData>();

    PermutationBuilder() {
        perm.add(new IndexData());
    }

    void insertAfter(int n) {
        IndexData newData = new IndexData();
        newData.before = n;
        newData.after = perm.get(n).after;
        perm.get(n).after = perm.size();
        perm.get(newData.after).before = perm.size();
        perm.add(newData);
    }

    void insertBefore(int n) {
        insertAfter(perm.get(n).before);
    }

    int[] getPermutation() {
        int result[] = new int[perm.size() - 1];
        int nextIndex = 0;
        int next = perm.get(0).after;
        while ( next != 0 ) {
            result[nextIndex++] = next;
            next = perm.get(next).after;
        }
        return result;
    }
}

//--------------------------- solve ---------------------------------

public class CableAccepted {

    static class Index2D {
        int x,y;
    }

    static boolean comparable(Index2D a, Index2D b) {
        return (a.x <= b.x && a.y <= b.y)
            || (a.x >= b.x && a.y >= b.y);
    }

    static int solve(Input input) {
        PermutationBuilder pb0 = new PermutationBuilder();
        PermutationBuilder pb1 = new PermutationBuilder();
        // initial switchbox (numbered 1)
        pb0.insertAfter(0);
        pb1.insertAfter(0);
        for ( Extension e : input.extensions ) {
            pb0.insertAfter(e.target);
            if ( e.type == 'P' )
                pb1.insertBefore(e.target);
            else
                pb1.insertAfter(e.target);
        }
        int orders[][] = { pb0.getPermutation(), pb1.getPermutation() };
        // build inverted index
        final int BOXES = input.extensions.length + 1;
        Index2D[] reachabilityIndex = new Index2D[BOXES + 1];
        for ( int i = 0; i < reachabilityIndex.length; i++ )
            reachabilityIndex[i] = new Index2D();
        for ( int i = 0; i < BOXES; i++ ) {
            reachabilityIndex[orders[0][i]].x = i;
            reachabilityIndex[orders[1][i]].y = i;
        }
        // process queries
        int reachableCount = 0;
        for ( Query q : input.queries )
            if ( comparable(reachabilityIndex[q.from], reachabilityIndex[q.to]) )
                reachableCount++;
        return reachableCount;
    }

    public static void main(String args[]) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        Input input = Input.parse(reader);
        System.out.println(solve(input));
    }

}
