import pandas as pd
import itertools as it

def checkSubset(subset,main):
    for ele in subset:
        if ele not in main:
            return False
    return True

def initializeVariables():
    df = pd.read_excel('database.xlsx')
    df.index=df['TID']
    df=df.drop('TID',axis=1)
    for row in df['Itemsets']:
        transaction=[]
        for item in row:
            if item != ',':
                transaction.append(item)
                if item not in uniq:
                    uniq[item]=1
                else:
                    uniq[item]+=1
        itemset.append(transaction)  
    for value,count in uniq.items():
        if count>=minsup:
            l.append(list(value)) 
    if l:
        for item in l:        
            freq.append(item)
    return df
        
def prune(c,l,k):
    remove=[]
    for index,c1 in enumerate(c):
        ctemp = it.combinations(list(c1),k-1)
        check=[list(temp) for temp in ctemp]
        for items in check:
            if checkSubset(items,l):
                if index not in remove:
                    remove.append(index)
    remove.sort()
    remove.reverse()
    for index in remove:
        c.pop(index)                
         
def gen_candidate_itemsets(l,k):
    c,c1=[],[]
    for i in range(0,len(l)-1):
        for j in range(i+1,len(l)):
            temp = list(set(l[i]+l[j]))
            ctemp = list(it.combinations(temp,k))
            if len(ctemp)>0:
                for r in ctemp:
                    if r not in c:
                        r=list(r)
                        r.sort()
                        c.append(r)
    for item in c:
        if item not in c1:
            c1.append(item)
    return c1

def generate_frequent_itemsets(l,c):
    support={}
    for item in c:
        support[tuple(item)]=0
        for transaction in itemset:
            if checkSubset(item,transaction):
                support[tuple(item)]+=1
    for value,count in support.items():
        if count>=minsup:
            l.append(list(value))
    if l:
        for item in l:        
            freq.append(item)
    return freq
                
def calculate_support(df,item):
    sup=0
    for index,row in df.iterrows():
        transaction = row['Itemsets'].split(',')
        if checkSubset(item,transaction):
            sup+=1
    return sup

def calculate_confidence(frequent_itemsets):
    for item in frequent_itemsets:
        if len(item)<2:
            continue
        print(f"\nRULES FOR {item}")
        k = len(item)
        for i in range(1,k):
            combinations = list(it.combinations(item,i))
            listcomb = [list(temp) for temp in combinations]
            for comb in listcomb:
                print(f"Confidence: {''.join(list(set(comb)))} -> {''.join(list(set(item)-set(comb)))} = {round(calculate_support(df,item=item)/calculate_support(df,item=comb),2)}")

if __name__=='__main__':
    minsup=int(input("Enter minimum support: "))
    uniq={}
    l,freq,itemset=[],[],[]
    df = initializeVariables()
    length=len(l)
    k=2
    while len(l)!=0:
        c=gen_candidate_itemsets(l,k)
        prune(c,l,k)
        l=[]
        generate_frequent_itemsets(l,c)
        k+=1
    c1=[]
    for item in freq:
        if item not in c1:
            c1.append(item)
    freq=c1
    print(freq)
    calculate_confidence(freq)
    