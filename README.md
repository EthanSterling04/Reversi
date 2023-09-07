# Reversi

Reversi is a strategy board game for two players, played on an 8×8 uncheckered board.

## Specification:

The game Reversi is played by two players, Dark and Light, laying dark- and light-colored tiles on an 8-by-8 board. The game proceeds in two phases.

In the opening phase, the players alternate turns, with Dark going first. In this phase, they may only play in the center four squares of the board ((3, 3), (3, 4), (4, 3), and (4, 4) if 0-based). The opening phase ends when those center four squares are occupied.

In the main phase, each move must capture at least one of the other player’s tiles, as follows. The current player places a tile in an unoccupied square so that it forms at least one straight line—horizontal, vertical, or diagonal—with one or more of the other player’s tiles in the middle and one of the current player’s tiles on the other end. Then the other player’s tiles in the line(s) are flipped to the current player.

The players take turns unless one player cannot play, in which case the other player may play again. The game is over when neither player can play. The winner is the player with more tiles on the final board (or it may be a tie).
