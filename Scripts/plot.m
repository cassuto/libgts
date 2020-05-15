tones = {"C","C#","D","D#","E","F","G","G#","A","A#","B","B#"};
chroma_tbl = load('chroma.csv', ',');

timescale = 1:12;
chroma = zeros(size(chroma_tbl,2)-1, size(chroma_tbl,1));
for i = 1:size(chroma_tbl,1)
    for j = 1:size(chroma_tbl,2)-1
        chroma(j,i) = chroma_tbl(i,j+1);
    end
    timescale(i) = chroma_tbl(i,1);
end

clf
h = heatmap(timescale, tones, chroma);
h.Title = 'Chromagram';
h.XLabel = 'Time (s)';
h.YLabel = 'Pitch';
colormap(jet);

