CREATE OR REPLACE FUNCTION SubmitReview(_paper_id INT, _reviewer_id INT, _score INT)
RETURNS VOID AS $$
DECLARE
    avg_score DOUBLE PRECISION;
BEGIN
    IF EXISTS (SELECT paper_id FROM PaperReviewing WHERE paper_id = _paper_id AND reviewer_id = _reviewer_id) AND (_score BETWEEN 1 AND 7) THEN
        UPDATE PaperReviewing SET score = _score WHERE paper_id = _paper_id AND reviewer_id = _reviewer_id;

        IF (SELECT COUNT(score) FROM PaperReviewing WHERE paper_id = _paper_id) = 3 THEN
            SELECT AVG(score) INTO avg_score FROM PaperReviewing WHERE paper_id = _paper_id;
            UPDATE Paper SET accepted = (CASE WHEN avg_score > 4 THEN TRUE ELSE FALSE END) WHERE id = _paper_id;
        END IF;
    ELSE
        RAISE EXCEPTION 'Invalid arguments';
    END IF;
END;
$$ LANGUAGE plpgsql;
