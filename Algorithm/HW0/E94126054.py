import matplotlib.pyplot as plt

class SavingAccount(object):
    def __init__(self, principal, rate, years):
        self.principal = principal
        self.rate = rate
        self.years = years
        self.principals = [principal]
        self.interests = [0.0]     
        self.legend = None           

    def add_interest(self):
        pass

    def get_total_interest(self):
        return self.interests[-1]

    def get_final_principal(self):
        return self.principals[-1]

    def __str__(self):
        return self.legend

    def plot_principals(self, style):
        plt.plot(self.principals, style, label=self.legend)

    def plot_interests(self, style):
        plt.plot(self.interests, style, label=self.legend)

class SimpleRate(SavingAccount):
    def __init__(self, principal, rate, years):
        SavingAccount.__init__(self, principal, rate, years)
        self.legend = f'Simple'

    def add_interest(self):
        interest = self.principal * self.rate
        new_principal = self.principals[-1] + interest
        self.principals.append(new_principal)
        total_interest = self.interests[-1] + interest
        self.interests.append(total_interest)

class CompoundRate(SavingAccount):
    def __init__(self, principal, rate, years):
        SavingAccount.__init__(self, principal, rate, years)
        self.legend = f'Compound'

    def add_interest(self):
        interest = self.principals[-1] * self.rate
        new_principal = self.principals[-1] + interest
        self.principals.append(new_principal)
        total_interest = self.interests[-1] + interest
        self.interests.append(total_interest)
        
class TwoRates(SavingAccount):
    def __init__(self, principal, bonus_rate, normal_rate, bonus_years, total_years):
        SavingAccount.__init__(self, principal, bonus_rate, total_years)
        self.bonus_rate = bonus_rate
        self.normal_rate = normal_rate
        self.bonus_years = bonus_years
        self.legend = f'Two Rates'

    def add_interest(self):
        if len(self.principals) == self.bonus_years + 1:
            self.rate = self.normal_rate
            
        interest = self.principals[-1] * self.rate
        new_principal = self.principals[-1] + interest
        self.principals.append(new_principal)
        total_interest = self.interests[-1] + interest
        self.interests.append(total_interest)

def plot_savings(accounts):
    styles = ['k-', 'k--', 'k:']
    
    plt.figure(1)
    for i, account in enumerate(accounts):
        account.plot_principals(styles[i])
        
    plt.title('Accumulated Principal')
    plt.xlabel('Years')
    plt.ylabel('Principal $')
    plt.legend(loc='best')

    plt.figure(2)
    for i, account in enumerate(accounts):
        account.plot_interests(styles[i])
        
    plt.title('Accumulated Interests')
    plt.xlabel('Years')
    plt.ylabel('Interest $')
    plt.legend(loc='best')

    plt.show()

def compare_savings():
    PRINCIPAL = 1000000.0
    YEARS = 10
    SIMPLE_RATE = 0.015
    COMPOUND_RATE = 0.015
    BONUS_RATE = 0.030
    NORMAL_RATE = 0.015
    BONUS_YEARS = 3

    simple_acc = SimpleRate(PRINCIPAL, SIMPLE_RATE, YEARS)
    compound_acc = CompoundRate(PRINCIPAL, COMPOUND_RATE, YEARS)
    two_rates_acc = TwoRates(PRINCIPAL, BONUS_RATE, NORMAL_RATE, BONUS_YEARS, YEARS)
    
    accounts = [simple_acc, compound_acc, two_rates_acc]

    for year in range(YEARS):
        for account in accounts:
            account.add_interest()

    for account in accounts:
        if isinstance(account, TwoRates):
            print(f"Two Rates Saving Account - Principal: {account.principal} with bonus rate:{account.bonus_rate*100}% for {account.bonus_years} years, then with rate:{account.normal_rate*100}%")
        else:
            print(f"{type(account).__name__} Saving Account - Principal: {account.principal} with rate:{account.rate*100}%")

        print("Accumulated Interests Earned in 10 Years:")
        print([round(i, 1) for i in account.interests])
        
        print("Accumulated Principal in 10 Years:")
        print([round(p, 1) for p in account.principals])
        
        print(f"Total Interest Earned = {round(account.get_total_interest(), 1)}")
        print(f"Accumulated Principal = {round(account.get_final_principal(), 1)}")
        
        print("\n" + "-"*50 + "\n")

    plot_savings(accounts)

if __name__ == "__main__":
    compare_savings()