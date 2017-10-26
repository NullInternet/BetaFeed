# BetaFeed
Our Facebook page interfaces with our application to correlate highly-liked and commented posts with Facebook users. It will analyze the amount of likes/comments on each post and publish a list of the top users who respond the most, and which posts received the most responses. A potential use of this application is in rating games for beta testing to measure how much users liked or disliked the game on a weekly/monthly basis for game developers to measure public reaction to their games.

# Motivation
to create a analytical application that will gauge user reliability and post popularity by the number of responses each user makes on a post and the relative popularity of a post among a group of users.

# Short-Term Goals
The Facebook page features a few posts on different games (the game posts are just a title name plus an image for now). Our application keeps track of post IDs and what users clicked Like or commented on a post, and stores the information in a database (post IDs are associated with likes/comments, which are associated with visitor IDs). How many likes and comments each visitor has made on each post will influence their reliability ranking (like 1000 game reviewed = 1000 reputation points, affects a game's overall rating based on number of rep points). A list of game posts and user reliability scores are also stored by the database.

# Long-Term Goals
Include more posts to increase database entries. Periodically, our application will update the page with the users' top-rated games and most reliable user of the week/month.

# Group Members
Lola Holiday, Ken Hsu, John Lee, Tan Tran
