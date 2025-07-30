# python code for tic-tac-toe game
import random
class TicTacToe:
    def __init__(self):
        self.board = [' ' for _ in range(9)]
        self.current_winner = None  # keep track of winner!
        self.current_player = 'X'  # starting player
    def print_board(self):
        for row in [self.board[i * 3:(i + 1) * 3] for i in range(3)]:
            print('| ' + ' | '.join(row) + ' |')
    def play(self):
        while True:
            self.print_board()
            if self.current_player == 'X':
                square = self.get_player_move()
            else:
                square = self.get_computer_move()
            if self.make_move(square):
                if self.check_winner(square):
                    self.print_board()
                    print(f'Player {self.current_player} wins!')
                    return
                if ' ' not in self.board:
                    self.print_board()
                    print('It\'s a tie!')
                    return
                self.current_player = 'O' if self.current_player == 'X' else 'X'
    def get_player_move(self):
        while True:
            try:
                square = int(input(f'Player {self.current_player}, enter a square (0-8): '))
                if square >= 0 and square < 9 and self.board[square] == ' ':
                    return square
                else:
                    print('Invalid move. Try again.')
            except ValueError:
                print('Please enter a valid number between 0 and 8.')
    def get_computer_move(self):
        available_moves = [i for i, square in enumerate(self.board) if square == ' ']
        return random.choice(available_moves) if available_moves else None
    def make_move(self, square):
        if self.board[square] == ' ':
            self.board[square] = self.current_player
            return True
        return False
    def check_winner(self, square):
        row_ind = square // 3
        row = self.board[row_ind * 3:(row_ind + 1) * 3]
        if all(s == self.current_player for s in row):
            self.current_winner = self.current_player
            return True
        col_ind = square % 3
        column = [self.board[col_ind + i * 3] for i in range(3)]
        if all(s == self.current_player for s in column):
            self.current_winner = self.current_player
            return True
        if square % 2 == 0:
            diagonal1 = [self.board[i] for i in [0, 4, 8]]
            if all(s == self.current_player for s in diagonal1):
                self.current_winner = self.current_player
                return True
            diagonal2 = [self.board[i] for i in [2, 4, 6]]
            if all(s == self.current_player for s in diagonal2):
                self.current_winner = self.current_player
                return True
        return False
if __name__ == '__main__':
    game = TicTacToe()
    game.play()
# This code implements a simple Tic Tac Toe game where a player can play against the computer.