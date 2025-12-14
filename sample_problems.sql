-- Sample LeetCode problems to get started
-- Run this after the application creates the database tables

INSERT INTO problems (title, url, difficulty, category, status, time_spent, last_attempted) VALUES
-- Easy Problems (New)
('Two Sum', 'https://leetcode.com/problems/two-sum/', 0, 0, 0, 0, '2024-01-01T00:00:00'),
('Palindrome Number', 'https://leetcode.com/problems/palindrome-number/', 0, 0, 0, 0, '2024-01-01T00:00:00'),
('Roman to Integer', 'https://leetcode.com/problems/roman-to-integer/', 0, 0, 0, 0, '2024-01-01T00:00:00'),
('Valid Parentheses', 'https://leetcode.com/problems/valid-parentheses/', 0, 0, 0, 0, '2024-01-01T00:00:00'),
('Merge Two Sorted Lists', 'https://leetcode.com/problems/merge-two-sorted-lists/', 0, 0, 0, 0, '2024-01-01T00:00:00'),

-- Easy Problems (Incomplete)
('Remove Duplicates from Sorted Array', 'https://leetcode.com/problems/remove-duplicates-from-sorted-array/', 0, 1, 1, 450, '2024-01-02T10:30:00'),
('Remove Element', 'https://leetcode.com/problems/remove-element/', 0, 1, 1, 320, '2024-01-02T11:15:00'),
('Find the Index of the First Occurrence in a String', 'https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/', 0, 1, 1, 600, '2024-01-02T14:20:00'),

-- Easy Problems (Completed)
('Length of Last Word', 'https://leetcode.com/problems/length-of-last-word/', 0, 2, 2, 180, '2024-01-01T09:15:00'),
('Plus One', 'https://leetcode.com/problems/plus-one/', 0, 2, 2, 240, '2024-01-01T10:30:00'),
('Add Binary', 'https://leetcode.com/problems/add-binary/', 0, 2, 2, 420, '2024-01-01T15:45:00'),
('Sqrt(x)', 'https://leetcode.com/problems/sqrtx/', 0, 2, 2, 360, '2024-01-01T16:30:00'),

-- Medium Problems (New)
('Add Two Numbers', 'https://leetcode.com/problems/add-two-numbers/', 1, 0, 0, 0, '2024-01-01T00:00:00'),
('Longest Substring Without Repeating Characters', 'https://leetcode.com/problems/longest-substring-without-repeating-characters/', 1, 0, 0, 0, '2024-01-01T00:00:00'),
('Median of Two Sorted Arrays', 'https://leetcode.com/problems/median-of-two-sorted-arrays/', 1, 0, 0, 0, '2024-01-01T00:00:00'),
('Longest Palindromic Substring', 'https://leetcode.com/problems/longest-palindromic-substring/', 1, 0, 0, 0, '2024-01-01T00:00:00'),
('ZigZag Conversion', 'https://leetcode.com/problems/zigzag-conversion/', 1, 0, 0, 0, '2024-01-01T00:00:00'),

-- Medium Problems (Incomplete)
('Reverse Integer', 'https://leetcode.com/problems/reverse-integer/', 1, 1, 1, 720, '2024-01-02T13:45:00'),
('String to Integer (atoi)', 'https://leetcode.com/problems/string-to-integer-atoi/', 1, 1, 1, 900, '2024-01-02T16:20:00'),
('Container With Most Water', 'https://leetcode.com/problems/container-with-most-water/', 1, 1, 1, 540, '2024-01-02T17:30:00'),

-- Medium Problems (Completed)
('3Sum', 'https://leetcode.com/problems/3sum/', 1, 2, 2, 1200, '2024-01-01T14:20:00'),
('Letter Combinations of a Phone Number', 'https://leetcode.com/problems/letter-combinations-of-a-phone-number/', 1, 2, 2, 900, '2024-01-01T11:45:00'),
('Remove Nth Node From End of List', 'https://leetcode.com/problems/remove-nth-node-from-end-of-list/', 1, 2, 2, 600, '2024-01-01T13:15:00'),

-- Hard Problems (New)
('Regular Expression Matching', 'https://leetcode.com/problems/regular-expression-matching/', 2, 0, 0, 0, '2024-01-01T00:00:00'),
('Merge k Sorted Lists', 'https://leetcode.com/problems/merge-k-sorted-lists/', 2, 0, 0, 0, '2024-01-01T00:00:00'),
('Reverse Nodes in k-Group', 'https://leetcode.com/problems/reverse-nodes-in-k-group/', 2, 0, 0, 0, '2024-01-01T00:00:00'),
('Substring with Concatenation of All Words', 'https://leetcode.com/problems/substring-with-concatenation-of-all-words/', 2, 0, 0, 0, '2024-01-01T00:00:00'),

-- Hard Problems (Incomplete)
('Median of Two Sorted Arrays', 'https://leetcode.com/problems/median-of-two-sorted-arrays/', 2, 1, 1, 1800, '2024-01-02T19:30:00'),
('Longest Valid Parentheses', 'https://leetcode.com/problems/longest-valid-parentheses/', 2, 1, 1, 1500, '2024-01-02T20:45:00'),

-- Hard Problems (Completed)
('First Missing Positive', 'https://leetcode.com/problems/first-missing-positive/', 2, 2, 2, 2100, '2024-01-01T18:30:00'),
('Trapping Rain Water', 'https://leetcode.com/problems/trapping-rain-water/', 2, 2, 2, 1800, '2024-01-01T20:15:00');

-- Sample daily session for today (adjust date as needed)
INSERT INTO daily_sessions (date, problem_ids, completed) VALUES
('2024-01-03', '9,10,6,7,1,2,3', 0);